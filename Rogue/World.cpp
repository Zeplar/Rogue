#include "stdafx.h"
#include "World.h"
#include "Tiles.h"
#include "Entity.h"
using namespace std;

ALLEGRO_BITMAP *World::display = NULL;
Chunk* World::chunks[WorldSize][WorldSize];
const int RenderDistance = 2;
ALLEGRO_TRANSFORM World::transforms[16];
int World::transform_index = 0;
std::vector<Entity*> World::players;
std::vector<bool> World::key(ALLEGRO_KEY_MAX, false); //Array indicating which keys were pressed last time we checked


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

bool World::Push_Matrix(const ALLEGRO_TRANSFORM *transform)
{
	if (transform && transform_index < 15) {
		al_copy_transform(&transforms[++transform_index], transform);
		al_compose_transform(&transforms[0], transform);
		al_use_transform(&transforms[0]);
		return true;
	}
	else {
		std::cerr << "Invalid transform or matrix stack overflow\n";
		return false;
	}
}

bool World::Pop_Matrix()
{
	if (transform_index > 0)
	{
		al_invert_transform(&transforms[transform_index]);
		al_compose_transform(&transforms[0], &transforms[transform_index]);
		al_use_transform(&transforms[0]);
		--transform_index;
		return true;
	}
	std::cerr << "Failed to pop matrix\n";
	return false;
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

Tile& World::getTile(const coord& c)
{
	int x = c.first;
	int y = c.second;
	return getTile(x, y);
}

void World::Update()
{
	int x, y;
	for each (Entity *p in players)
	{
		p->GetPosition(x, y);
		auto chunks = World::GetChunksAround(x,y);
		for each (Chunk *c in *chunks)
		{
			if (c == &Chunk::Impassable_Chunk()) continue;
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
std::unique_ptr<std::vector<Chunk*>> World::GetChunksAround(int x, int y)
{
	auto ret = make_unique<std::vector<Chunk*>>();
	for (int i = -RenderDistance; i <= RenderDistance; i++)
		for (int j = -RenderDistance; j <= RenderDistance; j++)
		{
			if (OutOfBounds(x / Chunk::size + i, y / Chunk::size + j)) 
				ret->push_back(&Chunk::Impassable_Chunk());
			else if (World::chunks[x / Chunk::size + i][y / Chunk::size + j] == NULL)
			{
				World::chunks[x / Chunk::size + i][y / Chunk::size + j] = Chunk::generateChunk(Chunk::chunk_generate_growth_sample(10, 4));
				ret->push_back(World::chunks[x / Chunk::size + i][y / Chunk::size + j]);
			}
			else
				ret->push_back(World::chunks[x / Chunk::size + i][y / Chunk::size + j]);
		}

	return ret;
}

//Draw the chunks in the render distance around the player
void World::Draw(int x, int y)
{
	GetChunksAround(x, y);
	int chunk_x = x / Chunk::size;
	int chunk_y = y / Chunk::size;
	al_set_target_bitmap(display);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	ALLEGRO_TRANSFORM temp;

	for (int i= - RenderDistance; i < RenderDistance; i++)
		for (int j = - RenderDistance; j < RenderDistance; j ++)
		{
			if (OutOfBounds(chunk_x + i, chunk_y + j)) continue;

			al_build_transform(&temp, i * Chunk::size * Tile::TILE_W, j * Chunk::size * Tile::TILE_H, 1, 1, 0);
			Push_Matrix(&temp);
			if (chunks[chunk_x + i][chunk_y + j] != NULL)
			{
				chunks[chunk_x + i][chunk_y + j]->Draw();
			}
			else std::cerr << "Null chunk where there shouldn't be\n";
			Pop_Matrix();
		}
}

void World::Initialize()
{
	Forest_Floor::Forest_Floor().RegisterImage();
	Forest_Tree::Forest_Tree().RegisterImage();
	al_identity_transform(&transforms[0]);
}

void World::RegisterPlayer(Entity *p)
{
	int x, y;
	players.push_back(p);
	p->GetPosition(x, y);
	World::GetChunksAround(x,y);
	World::getTile(x,y).entity = std::unique_ptr<Entity>(p);
	std::cout << "Playername: " << World::getTile(x, y).entity->name << std::endl;
}

void World::UnregisterPlayer(Entity *p) {
	throw new exception("Unimplemented function!\n");
}