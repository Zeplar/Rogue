#pragma once
#include "Tile.h"
class Chunk
{
public:
	Chunk();
	~Chunk();
	void Draw(int x, int y);
	static const int size = 16;
	Tile *data[size][size];

private:
	Chunk* neighbors[4];
	static Chunk* _impassable;	//Chunk referenced by Impassable_Chunk()
	static Chunk* Impassable_Chunk(); //Generates a chunk of all trees
	static Chunk * generateChunk();

	friend class World;
};

