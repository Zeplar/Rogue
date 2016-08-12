#include "stdafx.h"
#include "Entity.h"
#include "Tile.h"

Entity::Entity()
{
}

void Entity::Draw()
{
	al_draw_rotated_bitmap(image, al_get_bitmap_width(image) / 2, al_get_bitmap_height(image) / 2,
		x * Tile::TILE_W + Tile::TILE_W / 2,
		y * Tile::TILE_H + Tile::TILE_H / 2,
		getDirection(direction) + M_PI, 0);
}

double Entity::getDirection(int Entity_Direction)
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

//Fills in the x,y offset to the tile the player is looking at
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

Entity::~Entity()
{
}
