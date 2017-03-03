#include "stdafx.h"
#include "Chunk.h"
#include "World.h"

json Chunk::serialize()
{
	std::vector<int> tiles;
	for (auto &tile : data)
	{
		tiles.push_back(tile->id);
	}
	return json(tiles);
}

Chunk::Chunk(json& chunkFile)
{
	data = std::vector<Tile*>();
	for (int tileID : chunkFile)
	{
		data.push_back(new Tile(tileID));
	}
}

Chunk::Chunk()
{
	data = std::vector<Tile*>(size*size);
}

Chunk::~Chunk()
{
	for each (Tile *var in data)
	{
		delete var;
	}
}

void Chunk::Draw()
{
	ALLEGRO_TRANSFORM temp;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) {
			al_build_transform(&temp, i*Tile::TILE_W, j*Tile::TILE_H, 1, 1, 0);
			World::Push_Matrix(&temp);
			data[i*size+j]->Draw();
			World::Pop_Matrix();
		}
}

Chunk::Chunk(std::vector<int>* sample)
{
	data = std::vector<Tile*>(size*size);
	for (int i = 0; i < Chunk::size; i++)
		for (int j = 0; j < Chunk::size; j++)
		{
			if (sample->at(i*Chunk::size + j))
			{
				data[i*size+j] = new Tile(Tile::baseTiles[1]);
			}
			else
				data[i*size+j] = new Tile(Tile::baseTiles[0]);
		}
}


std::vector<int>* Chunk::chunk_generate_growth_sample(int initial_seeds, int size)
{
	const int l = Chunk::size * Chunk::size;
	const int nghbrs[8] = { -Chunk::size - 1, -Chunk::size, -Chunk::size + 1, -1, 1, Chunk::size - 1, Chunk::size, Chunk::size + 1 };
	std::vector<int>* sample = new std::vector<int>(l);
	std::vector<int> treeLocations;
	int tree = 0;
	
	for (int i = 0; i < initial_seeds; i++)
	{
		treeLocations.push_back(rand() % l);
		sample->at(treeLocations.back()) = 1;
	}

	for (int i = 0; i < initial_seeds * size * size; i++)
	{
		tree = treeLocations[rand() % treeLocations.size()];
		int x = tree + nghbrs[rand() % 8];
		if (x > 0 && x < l)
		{
			sample->at(x) = 1;
			treeLocations.push_back(x);
		}
	}
	return sample;

}



std::vector<int> * Chunk::chunk_generate_cell_sample(int minimum, int optimal, int maximum, int rounds)
{
	const int l = (Chunk::size) * (Chunk::size);
	const int nghbrs[8]{ -Chunk::size - 1, -Chunk::size, -Chunk::size + 1, -1, 1, Chunk::size - 1, Chunk::size, Chunk::size + 1 };

	std::vector<int> *sample = new std::vector<int>();
	std::vector<int> neighbors;
	for (int i = 0; i < l; i++)
	{
		sample->push_back(std::rand() % 2);
		neighbors.push_back(0);
	}
	for (int t = 0; t < rounds; t++)
	{
		for (int i = 0; i < l; i ++)
		{
			for (int x = 0; x < 8; x++)
				if (i + nghbrs[x] > 0 && i + nghbrs[x] < l)
					neighbors[i] += sample->at(i + nghbrs[x]);
		}
		for (int i = 0; i < l; i++)
		{
			if (neighbors[i] < minimum)
				sample->at(i) = 0;
			else if (neighbors[i] < optimal)
			{
			}
			else if (neighbors[i] < maximum)
				sample->at(i) = 1;
			else sample->at(i) = 0;
		}
	}

	return sample;
}







Chunk *Chunk::_impassable;

Chunk* Chunk::Impassable_Chunk()
{
	if (!_impassable) {
		_impassable = new Chunk();
		for (int i = 0; i < Chunk::size*Chunk::size; i++)
				_impassable->data[i] = Tile::impassable_tile;
	}

	return _impassable;
}
