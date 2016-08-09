#include "stdafx.h"
#include "Chunk.h"

Chunk::Chunk()
{

}

Chunk::~Chunk()
{
	for each (Tile *var in data)
	{
		delete var;
	}
}

void Chunk::Draw(int x, int y)
{
	
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			data[i][j]->Draw(i*Tile::TILE_W + x, j*Tile::TILE_H + y);
}
