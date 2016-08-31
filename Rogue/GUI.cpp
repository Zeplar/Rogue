#include "stdafx.h"
#include "GUI.h"
#include "Tile.h"
#include "World.h"

GUI::StatusBar::StatusBar(const int & x, const int & y, const int & var, const int & max_value, ALLEGRO_COLOR color) : x(x), y(y), var(var), max(max_value), color(color)
{
}

GUI::StatusBar::~StatusBar()
{
}

void GUI::StatusBar::Draw()
{
	ALLEGRO_TRANSFORM temp;
	al_build_transform(&temp, 0, -Tile::TILE_W / 4, 1, 1, 0);
	World::Push_Matrix(&temp);
	int length = (30 * var) / 100;
	std::cout << "(30 * " << var << ") / " << max << " = " << length << std::endl;
	al_draw_filled_rectangle(0, 0, length, 8, color);
	al_draw_rectangle(0, 0, Tile::TILE_W, 8, al_color_name("white"), 1);

	World::Pop_Matrix();
}

GUI::DirectionArrow::DirectionArrow(const Entity::Direction& direction) : direction(direction)
{	
}

GUI::DirectionArrow::~DirectionArrow()
{
}

void GUI::DirectionArrow::Draw()
{
	auto display = al_get_target_bitmap();
	auto temp = al_create_bitmap(Tile::TILE_W, Tile::TILE_H * 2);
	al_set_target_bitmap(temp);
	al_draw_filled_triangle(0, Tile::TILE_H, Tile::TILE_W, Tile::TILE_H, Tile::TILE_W / 2, 2*Tile::TILE_H, al_color_name("white"));
	al_set_target_bitmap(display);
	al_draw_scaled_rotated_bitmap(temp, Tile::TILE_W / 2, -Tile::TILE_H, Tile::TILE_W / 2, Tile::TILE_H / 2,
		.25, .25, Entity::getDirection(direction) + M_PI, 0);
	al_destroy_bitmap(temp);

}



GUI::Avatar::Avatar(ALLEGRO_BITMAP * image) : image(image)
{
}

GUI::Avatar::~Avatar()
{
	al_destroy_bitmap(image);
}

void GUI::Avatar::Draw()
{
	al_draw_bitmap(image, 0, 0, 0);
}