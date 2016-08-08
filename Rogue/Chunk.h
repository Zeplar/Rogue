#pragma once
#include "Tile.h"
class Chunk
{
public:
	Chunk();
	~Chunk();
	static const int size = 16;
	Tile *data[size][size];
	void Draw();
};

