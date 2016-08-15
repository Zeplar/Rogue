#pragma once
//Stores all of the code related to updating the terrain

#include <list>
#include "stdafx.h"
#include <time.h>
#include "Tile.h"
#include "Chunk.h"
#include <random>

class World
{
public:
	static const int WorldSize = 128;

	static bool OutOfBounds(int x, int y); //True if the given chunk is outside the chunk array

	static bool TileOutOfBounds(int x, int y);

	static void SetDisplay(ALLEGRO_BITMAP *display);

	static std::unique_ptr<std::vector<Chunk*>> GetChunksAround(int x, int y);

	static void Draw(int x, int y);

	static void Initialize();



	static Tile& getTile(int x, int y);

	static Tile& getTile(const coord & c);

	static void Update();

	static bool Push_Matrix(const ALLEGRO_TRANSFORM *transform);
	static bool Pop_Matrix();

	static std::vector<bool> key; //Array indicating which keys were pressed last time we checked

	static void RegisterPlayer(Entity * p);

	static void UnregisterPlayer(Entity *p);

private:
	static Chunk* chunks[WorldSize][WorldSize];
	static ALLEGRO_BITMAP *display;
	static ALLEGRO_TRANSFORM transforms[16];
	static int transform_index;
	static std::vector<Entity*> players;

};

