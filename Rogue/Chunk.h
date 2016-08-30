#pragma once
#include "Tile.h"

//Composite of tiles that get generated, loaded, or rendered all at the same time
//Might consider a quadtree approach in the future to make generating biomes more intuitive
class Chunk
{
public:
	~Chunk();
	void Draw();
	static const int size = 16;
	Tile *data[size][size];

private:
	Chunk();
	static Chunk *_impassable;	//Chunk referenced by Impassable_Chunk() so we don't have to keep generating the same chunk
	static Chunk *Impassable_Chunk(); //Generates a chunk of impassable trees to act as the game world border
	Chunk(std::vector<int>* sample);	//Helper function for converting a vector of ints into a chunk

	static std::vector<int>* chunk_generate_growth_sample(int initial_seeds, int size);	//

	static std::vector<int>* chunk_generate_cell_sample(int minimum, int optimal, int maximum, int rounds);

	friend class World;
};

