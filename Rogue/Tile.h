#pragma once
#include <allegro5\allegro_color.h>
#include <allegro5\allegro_image.h>


class Tile
{

public:
	Tile(ALLEGRO_BITMAP *image, bool canBeWalked = true);
	~Tile();
	void Draw(int x, int y);
	static Tile *Forest();
	static Tile *Forest_Floor();
	const bool walkable;
	const ALLEGRO_BITMAP *image;


	static const int TILE_W = 30;
	static const int TILE_H = 30;
};

