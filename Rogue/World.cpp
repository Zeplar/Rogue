#include "stdafx.h"
#include "World.h"

using namespace std;

ALLEGRO_BITMAP *World::display = NULL;
Chunk* World::chunks[WorldSize][WorldSize];


Chunk* World::generateChunk()
{
	Chunk *chunk = new Chunk();
	for (int i = 0; i < Chunk::size; i++)
		for (int j = 0; j < Chunk::size; j++)
		{
			if (std::rand() % 2)
			{
				chunk->data[i][j] = new Forest_Tree();
			} else
				chunk->data[i][j] = new Forest_Floor();
		}
	return chunk;
}

void World::SetDisplay(ALLEGRO_BITMAP *display)
{
	World::display = display;
}

Tile* World::getTile(int x, int y)
{
	return chunks[x / Chunk::size][y / Chunk::size]->data[x % Chunk::size][y % Chunk::size];
}



void World::GetChunksAroundPlayer(Player *p)
{
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			if (World::chunks[p->x / Chunk::size + i][p->y / Chunk::size + j] == NULL)
			{
				World::chunks[p->x / Chunk::size + i][p->y / Chunk::size + j] = generateChunk();
			}
}

void World::Draw()
{
	GetChunksAroundPlayer(Player::primaryPlayer);

	al_set_target_bitmap(display);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	for (int i=0; i < 4; i++)
		for (int j = 0; j < 4; j ++)
		{
			if (chunks[i][j] != NULL)
			{
				chunks[i][j]->Draw(i*Tile::TILE_W*Chunk::size, j*Tile::TILE_H*Chunk::size);
			}
		}
}

void World::Initialize()
{
	Forest_Floor::Forest_Floor().RegisterImage();
	Forest_Tree::Forest_Tree().RegisterImage();
	Draw();
}