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

	friend class World;
};

