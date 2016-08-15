#pragma once
#include "Tile.h"
class Chunk
{
public:
	Chunk();
	~Chunk();
	void Draw();
	static const int size = 16;
	Tile *data[size][size];

private:
	static Chunk *_impassable;	//Chunk referenced by Impassable_Chunk()
	static Chunk& Impassable_Chunk(); //Generates a chunk of all trees
	static Chunk * generateChunk(std::vector<int>* sample);

	static std::vector<int>* chunk_generate_growth_sample(int initial_seeds, int size);

	static std::vector<int>* chunk_generate_cell_sample(int minimum, int optimal, int maximum, int rounds);

	friend class World;
};

