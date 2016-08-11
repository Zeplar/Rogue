#pragma once
//Stores all of the code related to updating the terrain

#include <list>
#include "stdafx.h"
#include <time.h>
#include "Tile.h"
#include "Chunk.h"
#include "Forest_Floor.h"
#include "Forest_Tree.h"
#include <random>
#include "Player.h"


class World
{
public:
	static const int WorldSize = 128;

	static bool OutOfBounds(int x, int y); //True if the given chunk is outside the chunk array

	static bool TileOutOfBounds(int x, int y);

	static void SetDisplay(ALLEGRO_BITMAP *display);

	static void GetChunksAroundPlayer(Player * p);

	static void Draw(Player * p);

	static void Initialize();

	static Tile* getTile(int x, int y);

private:
	static Chunk* chunks[WorldSize][WorldSize];
	static ALLEGRO_BITMAP *display;
};

