#pragma once
#include "stdafx.h"
#include <vector>

class Tile
{
	friend class World;
public:
	Tile();
	~Tile();
	virtual bool isWalkable() = 0;
	void Draw(int x, int y);

	static int RegisterImage(const char TileName[]);	//Searches for the given image and creates an ALLEGRO_BITMAP in the Tiles registry.
	static int RegisterImage(ALLEGRO_BITMAP *image);	//Assigns the given image to the Tiles registry.

	static const int TILE_W = 30;
	static const int TILE_H = 30;

protected:
	static std::vector<ALLEGRO_BITMAP*> AllTiles;
	virtual int RegisterImage() = 0;	//Should call exactly one of the predefined RegisterImage() commands to add an image to the Tiles registry and receive an ID.
	static int numTiles;
	int TileID;

};

