#include "stdafx.h"
#include "Entity.h"
#include "Tile.h"
#include "World.h"

Entity::Entity(std::string name)
{
	this->name = name;
}


void Entity::Draw()
{
	for each (auto drawable in drawable_components)
		drawable->Draw();

	//al_draw_rectangle(0, 0, Tile::TILE_W, Tile::TILE_H, al_color_name("red"), 2);

}

Tile & Entity::getTile()
{
	return World::getTile(x, y);
}

void Entity::SetPosition(int x, int y)
{
	this->x = x; this->y = y;
}

void Entity::GetPosition(int& x, int &y) const
{
	x = this->x; y = this->y;
}

//Takes an Entity::Direction and returns a direction in radians
double Entity::getDirection(Entity::Direction Entity_Direction)
{
	switch (Entity_Direction) {
	case Direction::N:
		return 0;
	case Direction::NE:
		return M_PI_4;
	case Direction::E:
		return M_PI_2;
	case Direction::SE:
		return M_PI_2 + M_PI_4;
	case Direction::S:
		return M_PI;
	case Direction::SW:
		return M_PI + M_PI_4;
	case Direction::W:
		return -M_PI_2;
	case Direction::NW:
		return -M_PI_4;
	default:
		throw new std::invalid_argument("Unknown direction in Entity::getDirection\n");
	}
}

//Gets the entity's current direction as an x,y offset
void Entity::getDirection(int & dx, int & dy)
{
	switch (direction)
	{
	case Direction::N:
	case Direction::NE:
	case Direction::NW:
		dy = -1;
		break;
	case Direction::S:
	case Direction::SW:
	case Direction::SE:
		dy = 1;
		break;
	default:
		dy = 0;
		break;
	}
	switch (direction)
	{
		case Direction::NE:
		case Direction::E:
		case Direction::SE:
			dx = 1;
			break;
		case Direction::NW:
		case Direction::W:
		case Direction::SW:
			dx = -1;
			break;
		default:
			dx = 0;
			break;
	}
}

void Entity::SetDirection(int & dx, int & dy)
{
	if (dy < 0) 
	{
		if (dx > 0) direction = Entity::Direction::NE;
		else if (dx < 0) direction = Entity::Direction::NW;
		else direction = Entity::Direction::N;
	}
	else if (dy > 0) 
	{
		if (dx > 0) direction = Direction::SE;
		else if (dx < 0) direction = Direction::SW;
		else direction = Direction::S;
	}
	else 
	{
		if (dx < 0) direction = Direction::W;
		else if (dx > 0) direction = Direction::E;
	}

}

Entity::~Entity()
{
}
