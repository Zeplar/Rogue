#pragma once
//Stores all of the code related to updating the terrain

#include <list>
#include "stdafx.h"
#include <time.h>
#include "Tile.h"
#include "Chunk.h"
#include <random>
#include "Player.h"


class World
{
public:
	static const int WorldSize = 128;

	static bool OutOfBounds(int x, int y); //True if the given chunk is outside the chunk array

	static bool TileOutOfBounds(int x, int y);

	static void SetDisplay(ALLEGRO_BITMAP *display);

	static std::unique_ptr<std::vector<Chunk*>> GetChunksAroundEntity(const Entity& entity);

	static void Draw(const Player& p);

	static void Initialize();

	static Tile& getTile(int x, int y);

	static Tile& getTile(coord & c);

	static void Update();

private:
	static Chunk* chunks[WorldSize][WorldSize];
	static ALLEGRO_BITMAP *display;
};

