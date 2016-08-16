#include "stdafx.h"
#include "World.h"
#include "Tiles.h"
#include "Entity.h"
using namespace std;

ALLEGRO_BITMAP *World::display = NULL;
std::map<coord, Chunk, World::cmpCoord> World::chunks;
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
	auto& chunk = chunks[coord(x / Chunk::size, y / Chunk::size)];
	
	return *chunk.data[x % Chunk::size][y % Chunk::size];
}

Tile& World::getTile(const coord& c)
{
	int x = c.first;
	int y = c.second;
	return getTile(x, y);
}

Chunk & World::getChunk(int x, int y)
{
	if (OutOfBounds(x, y)) return Chunk::Impassable_Chunk();
	return chunks[coord(x / WorldSize, y % WorldSize)];
}

void World::Update()
{
	int x, y;
	for each (Entity *p in players)
	{
		p->GetPosition(x, y);
		auto chunks = World::GetChunksAround(x,y);
		for each (auto c in *chunks)
		{
			if (c.second == &Chunk::Impassable_Chunk()) continue;
			for each (Tile *t in c.second->data)
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
std::unique_ptr<std::map<coord, Chunk*, World::cmpCoord>> World::GetChunksAround(int x, int y)
{
	auto ret = make_unique<std::map<coord, Chunk*, World::cmpCoord>>();
	for (int i = (x / Chunk::size) - RenderDistance; i < (x / Chunk::size) + RenderDistance; i++)
		for (int j = (y / Chunk::size) - RenderDistance; j < (y / Chunk::size) + RenderDistance; j++)
		{
			coord chunk(i,j);
			if (OutOfBounds(chunk.first, chunk.second))
			{
				(*ret)[chunk] = (&Chunk::Impassable_Chunk());
			}
			else if (World::chunks.find(chunk) == chunks.end())
			{
				World::chunks[chunk] = *Chunk::generateChunk(Chunk::chunk_generate_growth_sample(10, 4));
				(*ret)[chunk] = (&World::chunks[chunk]);
			}
			else
				(*ret)[chunk] = (&World::chunks[chunk]);
		}

	return ret;
}

//Draw the chunks in the render distance around the player
void World::Draw(int x, int y)
{
	auto chunks = GetChunksAround(x, y);
	al_set_target_bitmap(display);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	ALLEGRO_TRANSFORM temp;

	for each (auto c in *chunks)
	{
		al_build_transform(&temp, c.first.first * Chunk::size * Tile::TILE_W, c.first.second * Chunk::size * Tile::TILE_H, 1, 1, 0);
		Push_Matrix(&temp);
		c.second->Draw();
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
}

void World::UnregisterPlayer(Entity *p) {
	throw new exception("Unimplemented function!\n");
}