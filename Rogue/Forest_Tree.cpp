#include "stdafx.h"
#include "Forest_Tree.h"

int Forest_Tree::ID = 0;

Forest_Tree::Forest_Tree()
{
	TileID = ID;
}


Forest_Tree::~Forest_Tree()
{
}

int Forest_Tree::RegisterImage()
{
	ALLEGRO_BITMAP *image = al_create_bitmap(Tile::TILE_W, Tile::TILE_H);
	if (image == NULL) fprintf(stderr, "Null image created under RegisterImage()\n");

//Grassy ground
	ALLEGRO_BITMAP *raw = al_load_bitmap("C:/Users/JHep/Documents/Visual Studio 2015/Projects/Rogue/Rogue/Rogue/tiles/Forest_Floor.bmp");
	if (raw == NULL) fprintf(stderr, "Null raw created under RegisterImage()\n");
	al_set_target_bitmap(image);
	al_draw_scaled_bitmap(raw, 0, 0, al_get_bitmap_width(raw), al_get_bitmap_height(raw), 0, 0, Tile::TILE_W, Tile::TILE_H, 0);
	al_destroy_bitmap(raw);

//Tree
	raw = al_load_bitmap("C:/Users/JHep/Documents/Visual Studio 2015/Projects/Rogue/Rogue/Rogue/tiles/Forest_Tree.bmp");
	if (!raw) fprintf(stderr, "Null raw created under RegisterImage()\n");
	al_convert_mask_to_alpha(raw, al_color_name("white"));
	al_draw_scaled_bitmap(raw, 0, 0, al_get_bitmap_width(raw), al_get_bitmap_height(raw), 0, 0, Tile::TILE_W, Tile::TILE_H, 0);
	al_destroy_bitmap(raw);

	ID = Tile::RegisterImage(image);
	fprintf(stderr, "Forest_Tree ID: %d\n", ID);

	return ID;
}


bool Forest_Tree::isWalkable()
{
	return false;
}