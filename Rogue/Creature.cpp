#include "stdafx.h"
#include "Creature.h"
#include "World.h"
#include "Player.h"
#include "GUI.h"

ALLEGRO_SAMPLE *Creature::sound_attack;

void Creature::Update()
{
	moveTimer++;
	Behavior();
}

Creature::Creature(std::string name) : Entity(name)
{
	drawable_components.push_back(new GUI::StatusBar(x, y, hp, 100, al_color_name("red")));
}

//Releases the tile pointer to this creature
void Creature::Die()
{
	World::getTile(x, y).entity.release();
}

//Takes damage and calls virtual Die() if hp <= 0
void Creature::takeDamage(int damage, Entity & source)
{
	hp -= damage;
	if (hp <= 0)
		Die();
}

//Returns true if the chessboard distance of the entity is less than or equal to <+range>
bool Creature::IsInRange(const Entity& entity, int range)
{
	int dx, dy;
	entity.GetPosition(dx, dy);
	return (std::abs(dx - x) <= range && std::abs(dy - y) <= range);
}


Entity* Creature::Find_Target_Player(int range)
{
	auto chunks = World::GetChunksAround(x, y);
	for each (auto c in *chunks)
		for each (Tile *t in c.second->data)
			if (t->entity && dynamic_cast<Player*>(t->entity.get()) && IsInRange(*t->entity, range))
			{
				return &*t->entity;
			}
	return nullptr;
}

void Creature::MoveTowardTarget()
{
	if (!target) return;
	int x, y;
	target->GetPosition(x, y);
	int dx = (x > this->x) - (x < this->x);
	int dy = (y > this->y) - (y < this->y);

	Move(dx, dy);
}

//Attempt to move in the given direction
void Creature::Move(int dx, int dy)
{
	SetDirection(dx, dy);
	Tile& target = World::getTile(x + dx, y + dy);
	Tile& original = World::getTile(x, y);
	if (target.Characteristics()[movementType] && !target.entity)
	{
		x += dx;
		y += dy;
		target.entity = std::move(original.entity);
	}

}

class Creature::A_Star
{

private:

	static int coord_to_index(Coord& c, int radius)
	{
		return (c.x + radius) * 2 * radius + c.y + radius;
	}

	static Coord index_to_coord(int index, int radius)
	{
		return Coord(index / radius / 2 - radius, index % (2 * radius) - radius, true);
	}

	static std::vector<int> neighbors(int index, int radius)
	{
		std::vector<int> ret(8);
		ret[0] = index - 2 * radius - 1;
		ret[1] = ret[0] + 1;
		ret[2] = ret[1] + 1;
		ret[3] = index - 1;
		ret[4] = index + 1;
		ret[5] = index + 2 * radius - 1;
		ret[6] = ret[5] + 1;
		ret[7] = ret[6] + 1;
		return ret;
	}

	static int distance(Coord& a, Coord& b)
	{
		return std::max(a.x - b.x, a.y - b.y);
	}

	static std::unique_ptr<std::vector<Coord>> Reconstruct_Path(std::vector<int>& came_from, int current, int radius)
	{
		auto ret = std::make_unique<std::vector<Coord>>();
		int start = coord_to_index(Coord(0, 0,true), radius);
		ret->push_back(index_to_coord(current, radius));

		while (current != start)
		{
			ret->push_back(index_to_coord(current, radius));
			current = came_from[current];
		}
		return ret;
	}

public:
	static std::unique_ptr<std::vector<Coord>> FindPathTo(Creature& self, Coord start, Coord end, int radius_to_search, Tile::Characteristic movementType)
	{
		int size = radius_to_search * radius_to_search * 4;
		int x, y;
		Coord end_offset = Coord(end.x - start.x, end.y - start.y, true);
		int end_index = coord_to_index(end_offset, radius_to_search);

		//The set of nodes already evaluated
		std::vector<int> closed_set;

		//The set of discovered nodes waiting to be evaluated
		std::vector<int> open_set;

		open_set.push_back(coord_to_index(Coord(0,0,true), radius_to_search));

		//For each node, which node it can most efficiently be reached from.
		std::vector<int> came_from(size, open_set[0]);

		//For each node, the cost of getting from the start node to that node
		std::vector<int> gScore(size, INT32_MAX);
		gScore[open_set[0]] = 0;

		//For each node, the total cost of getting from the start node to the goal by passing by that node.
		std::vector<int> fScore(size, INT32_MAX);
		fScore[open_set[0]] = distance(end, start);

		if (!World::getTile(end.x, end.y).Characteristics()[movementType]) return 0;

		while (!open_set.empty())
		{
			//current := element of open_set with minimum F value
			auto c = std::min_element(open_set.begin(), open_set.end(), [&fScore](int node1, int node2) {return fScore[node1] < fScore[node2]; });
			int current = *c;

			if (current == end_index)
				return Reconstruct_Path(came_from, current, radius_to_search);
			
			open_set.erase(c);
			closed_set.push_back(current);

			for each (int neighbor in neighbors(current, radius_to_search))
			{
				if (neighbor < 0 || neighbor >= 4 * radius_to_search*radius_to_search)
					continue;	//Ignore out-of-bounds
				if (std::find(closed_set.begin(), closed_set.end(), neighbor) != closed_set.end())
					continue;	//Ignore neighbors which have been evaluated

				x = index_to_coord(neighbor, radius_to_search).x + start.x;
				y = index_to_coord(neighbor, radius_to_search).y + start.y;

				if (!World::getTile(x, y).Characteristics()[movementType])
				{
					continue;	//Ignore tiles which are impassable
				}
				//Distance from start to neighbor

				int tentative_gScore = gScore[current] + 1;
				if ((std::find(open_set.begin(), open_set.end(), neighbor) == open_set.end()))
				{
					open_set.push_back(neighbor);
				}
				else if (tentative_gScore >= gScore[neighbor])
					continue;

				//This path is the best until now.
				came_from[neighbor] = current;

				gScore[neighbor] = tentative_gScore;
				Coord nghbr = index_to_coord(neighbor, radius_to_search);
				fScore[neighbor] = gScore[neighbor] + distance(nghbr, end);
			}


		}
		return 0;


	}
};

std::unique_ptr<std::vector<Coord>> Creature::FindPathTo(int x, int y, int radius_to_search)
{
	return A_Star::FindPathTo(*this, Coord(this->x, this->y,true), Coord(x, y,true), radius_to_search, movementType);
}