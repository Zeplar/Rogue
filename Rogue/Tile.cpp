#include "stdafx.h"
#include "Tile.h"
#include <allegro5\allegro_image.h>
#include <iostream>
#include <exception>



Tile::Tile(ALLEGRO_BITMAP *image, bool canBeWalked) : walkable( canBeWalked ), image (image)
{
}


Tile::~Tile()
{
	al_destroy_bitmap((ALLEGRO_BITMAP *)image);
}

void Tile::Draw(int x, int y)
{
	al_draw_bitmap((ALLEGRO_BITMAP *)image, x, y, 0);
}

Tile *Tile::Forest()
{
	ALLEGRO_BITMAP *image = al_create_bitmap(TILE_W, TILE_H);
	al_set_target_bitmap(image);

	ALLEGRO_BITMAP *raw = al_load_bitmap("C:/Users/JHep/Documents/Visual Studio 2015/Projects/Rogue/Rogue/Rogue/tiles/forest_floor.bmp");
	al_draw_scaled_bitmap(raw, 0, 0, al_get_bitmap_width(raw), al_get_bitmap_height(raw), 0, 0, TILE_W, TILE_H, 0);
	al_destroy_bitmap(raw);

	raw = al_load_bitmap("C:/Users/JHep/Documents/Visual Studio 2015/Projects/Rogue/Rogue/Rogue/tiles/forest.bmp");
	al_convert_mask_to_alpha(raw, al_color_name("white"));
	al_draw_scaled_bitmap(raw, 0, 0, al_get_bitmap_width(raw), al_get_bitmap_height(raw), 0, 0, TILE_W, TILE_H, 0);

	al_destroy_bitmap(raw);
	return new Tile(image);
}

Tile *Tile::Forest_Floor()
{
	ALLEGRO_BITMAP *raw = al_load_bitmap("C:/Users/JHep/Documents/Visual Studio 2015/Projects/Rogue/Rogue/Rogue/tiles/forest_floor.bmp");

	ALLEGRO_BITMAP *image = al_create_bitmap(TILE_W, TILE_H);
	al_set_target_bitmap(image);
	al_draw_scaled_bitmap(raw, 0, 0, al_get_bitmap_width(raw), al_get_bitmap_height(raw), 0, 0, TILE_W, TILE_H, 0);
	al_destroy_bitmap(raw);
	return new Tile(image, false);
}