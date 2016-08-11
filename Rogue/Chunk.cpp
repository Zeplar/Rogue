#include "stdafx.h"
#include "Chunk.h"
#include "Forest_Tree.h"

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

Chunk* Chunk::_impassable;

Chunk* Chunk::Impassable_Chunk()
{
	if (!_impassable) {
		_impassable = new Chunk();
		Forest_Tree* filler = new Forest_Tree();
		filler->SetCharacteristic(Tile::Characteristics::Flyable, false);
		for (int i = 0; i < 16; i++)
			for (int j = 0; j < 16; j++)
				_impassable->data[i][j] = filler;
	}

	return _impassable;
}
