#pragma once

#include "stdafx.h"
#include "Tile.h"
#include "Chunk.h"
#include <map>
#include <allegro5\events.h>


//Stores all of the code related to updating the terrain
class World
{
private:
	struct cmpCoord {
		bool operator()(const coord& a, const coord& b) const {
			return a.first < b.first ? true : a.first == b.first && a.second < b.second ? true : false;
		}
	};

public:
	static const int WorldSize = 128;

	static bool OutOfBounds(int x, int y); //True if the given chunk is outside the chunk array

	static bool TileOutOfBounds(int x, int y);

	static void SetDisplay(ALLEGRO_BITMAP *display);

	static void setTile(const coord & c, Tile * t);

	static std::unique_ptr<std::map<coord,Chunk*,World::cmpCoord>> GetChunksAround(int x, int y);

	static void Draw(int x, int y);

	static void Initialize();



	static Tile& getTile(int x, int y);

	static Tile& getTile(const coord & c);

	static Chunk& getChunk(int x, int y);

	static void Update();

	static bool Push_Matrix(const ALLEGRO_TRANSFORM *transform);
	static bool Pop_Matrix();

	static std::vector<bool> key; //Array indicating which keys were pressed last time we checked

	static std::tuple<bool,int, int> mouseEvent;	//First entry indicates a new event, next two entries are x,
	static std::tuple<bool, int, int> mouseDown;

	static void RegisterPlayer(Entity * p);

	static void UnregisterPlayer(Entity *p);

private:


	static std::map<coord, Chunk*, cmpCoord> chunks;
	static ALLEGRO_BITMAP *display;
	static ALLEGRO_TRANSFORM transforms[16];
	static int transform_index;
	static std::vector<Entity*> players;



};

