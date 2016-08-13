#include "stdafx.h"
#include "Creature.h"
#include "World.h"

void Creature::Update()
{
	moveTimer++;
	Behavior();
}

void Creature::takeDamage(int damage, Player & source)
{
	hp -= damage;
}

//Returns true if the chessboard distance of the entity is less than or equal to <+range>
bool Creature::IsInRange(const Entity& entity, int range)
{
	int dx, dy;
	entity.GetPosition(dx, dy);
	return (std::abs(dx - x) <= range && std::abs(dy - y) <= range);
}


void Creature::Find_Target_Player(int range)
{
	if (!(target && IsInRange(*target, range) && dynamic_cast<Player*>(target)))
	{
		auto chunks = World::GetChunksAroundEntity(*this);
		for each (Chunk *c in *chunks)
			for each (Tile *t in c->data)
				if (t->entity && dynamic_cast<Player*>(t->entity.get()) && IsInRange(*t->entity, range))
				{
					target = t->entity.get();
					return;
				}
	}
}

void Creature::MoveTowardTarget()
{
	if (!target) return;
	int x, y;
	target->GetPosition(x, y);
	int dx = x - this->x;
	int dy = y - this->y;

	Move(dx, dy);
}

void Creature::Move(int dx, int dy)
{
	Tile& target = World::getTile(x + dx, y + dy);
	Tile& original = World::getTile(x, y);
	if (target.Characteristics()[MovementType] && !target.entity)
	{
		x += dx;
		y += dy;
		target.entity = std::move(original.entity);
	}
}
