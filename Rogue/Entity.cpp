#include "stdafx.h"
#include "Entity.h"
#include "Tile.h"

Entity::Entity(std::string name)
{
	this->name = name;
}


void Entity::Draw()
{
	if (!image) std::cerr << "No image registered on entity\n";

	if (al_get_bitmap_width(image) > Tile::TILE_W * 8)
		al_draw_bitmap_region(image, Tile::TILE_W * direction, 0, Tile::TILE_W, Tile::TILE_H, 0, 0, 0);

	else
		al_draw_bitmap(image, 0, 0, 0);

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
		if (dy < 0) {
		if (dx > 0) direction = Entity::Direction::NW;
		else if (dx > 0) direction = Entity::Direction::NE;
		else direction = Entity::Direction::N;
	}
	else if (dy > 0) {
		if (dx > 0) direction = Direction::SE;
		else if (dx < 0) direction = Direction::SW;
		else direction = Direction::S;
	}
	else {
		if (dx < 0) direction = Direction::W;
		else if (dx > 0) direction = Direction::E;
		else direction = Direction::N;
	}

}

Entity::~Entity()
{
}
