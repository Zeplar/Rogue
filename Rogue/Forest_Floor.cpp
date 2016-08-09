#include "stdafx.h"
#include "Tile.h"
#include "Forest_Floor.h"

int Forest_Floor::ID = 0;

int Forest_Floor::RegisterImage()
{
	ID = Tile::RegisterImage("Forest_Floor.bmp");
	fprintf(stderr, "Forest_Floor ID: %d\n", ID);
	return ID;
}

Forest_Floor::Forest_Floor()
{
	TileID = ID;
}

Forest_Floor::~Forest_Floor()
{
}


bool Forest_Floor::isWalkable()
{
	return true;
}
