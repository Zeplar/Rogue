#include "stdafx.h"
#include "World.h"
#include "Tiles.h"
#include "Entity.h"
using namespace std;

ALLEGRO_BITMAP *World::display = NULL;
Chunk* World::chunks[WorldSize][WorldSize];
const int RenderDistance = 2;

//True if the given chunk is outside the chunk array
bool World::OutOfBounds(int x, int y)
{
	return x < 0 || y < 0 || x >= WorldSize || y >= WorldSize;
}

//True if the given tile is outside the chunk array
bool World::TileOutOfBounds(int x, int y)
{
	return x < 0 || y < 0 || x / Chunk::size > WorldSize || y / Chunk::size > WorldSize;
}



void World::SetDisplay(ALLEGRO_BITMAP *display)
{
	World::display = display;
}

//Returns the tile at the given coordinate
Tile& World::getTile(int x, int y)
{
	if (TileOutOfBounds(x, y)) return *Chunk::Impassable_Chunk().data[0][0];

	return *chunks[x / Chunk::size][y / Chunk::size]->data[x % Chunk::size][y % Chunk::size];
}

Tile& World::getTile(coord& c)
{
	int x = c.first;
	int y = c.second;
	return getTile(x, y);
}

void World::Update()
{
	for each (Player *p in Player::players)
	{
		auto chunks = World::GetChunksAroundEntity(*p);
		for each (Chunk *c in *chunks)
		{
			for each (Tile *t in c->data)
			{
				if (t->entity)
				{
					t->entity->Update();
				}
			}
		}
	}
}


//Generates the chunks RenderDistance radius around the given player, if they have not already been generated.
std::unique_ptr<std::vector<Chunk*>> World::GetChunksAroundEntity(const Entity& entity)
{
	auto ret = make_unique<std::vector<Chunk*>>();
	for (int i = -RenderDistance; i <= RenderDistance; i++)
		for (int j = -RenderDistance; j <= RenderDistance; j++)
		{
			if (OutOfBounds(entity.x / Chunk::size + i, entity.y / Chunk::size + j)) continue;
			else if (World::chunks[entity.x / Chunk::size + i][entity.y / Chunk::size + j] == NULL)
			{
				World::chunks[entity.x / Chunk::size + i][entity.y / Chunk::size + j] = Chunk::generateChunk(Chunk::chunk_generate_growth_sample(10, 4));
			}
			ret->push_back(World::chunks[entity.x / Chunk::size + i][entity.y / Chunk::size + j]);
		}

	return ret;
}

//Draw the chunks in the render distance around the player
void World::Draw(const Player& p)
{
	GetChunksAroundEntity(p);

	al_set_target_bitmap(display);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	for (int i= p.x / Chunk::size - RenderDistance; i < p.x / Chunk::size + RenderDistance; i++)
		for (int j = p.y / Chunk::size - RenderDistance; j < p.y / Chunk::size + RenderDistance; j ++)
		{
			if (OutOfBounds(i, j)) Chunk::Impassable_Chunk().Draw(i*Tile::TILE_W *Chunk::size, j*Tile::TILE_H * Chunk::size);
			else if (chunks[i][j] != NULL)
			{
				chunks[i][j]->Draw(i*Tile::TILE_W*Chunk::size, j*Tile::TILE_H*Chunk::size);
			}
			else {fprintf(stderr, "Null chunk where there shouldn't be.\n"); }
		}
}

void World::Initialize()
{
	Forest_Floor::Forest_Floor().RegisterImage();
	Forest_Tree::Forest_Tree().RegisterImage();
}