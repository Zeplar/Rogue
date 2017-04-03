#pragma once

#include "stdafx.h"
#include "Tile.h"
#include "Chunk.h"
#include <map>
#include <allegro5\events.h>
#include "Updateable.h"


//Stores all of the code related to updating the terrain
class World
{
private:
	//Returns the alphanumeric key being pressed.
	//This function updates a buffer once/Update.
	//TODO: Add shift, caps, space, etc.
	static char getKey();


public:
	static const int WorldSize = 128;

	static std::vector<Updateable*> updateable;

	//Returns a json object with all tile ids
	static json serializeTiles();

	static void loadChunks(json & chunkFile);


	static char keyPress;

	//Time since the keyPress changed. This allows functions to delay input when holding down a key.
	//This is expressed in units of Update() cycles since keyPress changed.
	static int timePressed;


	static bool OutOfBounds(int x, int y); //True if the given chunk is outside the chunk array

	static bool TileOutOfBounds(int x, int y);

	static void SetDisplay(ALLEGRO_BITMAP *display);

	static void setTile(const Coord & c, Tile * t);

	//Returns the chunk containing the given tile coordinate.
	static Chunk& getChunk(const Coord & c);

	static std::unique_ptr<std::map<Coord,Chunk*>> GetChunksAround(int x, int y);

	static void Draw(int x, int y);

	static void Initialize();



	static Tile& getTile(int x, int y);

	static Tile& getTile(const Coord & c);

	static void Update();

	static bool Push_Matrix(const ALLEGRO_TRANSFORM *transform);
	static bool Pop_Matrix();

	static std::vector<bool> key; //Array indicating which keys were pressed last time we checked

	static Coord mouseEvent;
	static Coord mouseDown;

	static void RegisterPlayer(Entity * p);

	static void UnregisterPlayer(Entity *p);
	static int RenderDistance;


private:

	static Chunk& getChunk(int x, int y);
	static std::map<Coord, Chunk*> chunks;
	static ALLEGRO_BITMAP *display;
	static ALLEGRO_TRANSFORM transforms[16];
	static int transform_index;
	static std::vector<Entity*> players;

};

