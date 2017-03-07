#include "stdafx.h"
#include "World.h"
#include "Tiles.h"
#include "Entity.h"
using namespace std;

ALLEGRO_BITMAP *World::display = NULL;
std::map<Coord, Chunk*> World::chunks;
const int RenderDistance = 2;
ALLEGRO_TRANSFORM World::transforms[16];
int World::transform_index = 0;
std::vector<Entity*> World::players;
std::vector<bool> World::key(ALLEGRO_KEY_MAX, false); //Array indicating which keys were pressed last time we checked
Coord World::mouseEvent;
Coord World::mouseDown;
std::vector<Updateable*> World::updateable;
char World::keyPress = 0;
int World::timePressed = 0;


char World::getKey()
{
	char ret = 0;
	
	for (int i = 1; i <= 36; i++) //1-26 are letters, 27-36 are numbers starting with 0
	{
		if (key[i]) {
			ret = i;
			break;
		}
	}
	if (ret == 0) return 0; //no alphanumeric key was pressed
	else if (ret >= 27) return ret - 27 + '0';
	else return ret - 1 + 'a';
}

json World::serializeTiles()
{
	json j;
	for (auto& chunk : chunks)
		j[chunk.first.x][chunk.first.y] = chunk.second->serialize();
	return j;
}

void World::loadChunks(json& chunkFile)
{
	int x = 0;
	int y = 0;
	std::cout << chunkFile << std::endl;
	for (auto& chunkX : chunkFile)
	{
		for (auto& chunkY : chunkX)
		{
			auto chunk = new Chunk(chunkY);
			chunks[Coord(x, y,true)] = chunk;
			y++;

		}
		x++;
	}

}

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

void World::setTile(const Coord& c, Tile* t)
{
	if (!c.tile) throw Coord::CoordExcept();
	if (TileOutOfBounds(c.x, c.y)) return;
	auto& chunk = chunks[Coord(c.x / Chunk::size, c.y / Chunk::size, true)];
	auto& tile = chunk->data[(c.x % Chunk::size)*Chunk::size + (c.y % Chunk::size)];
	t->entity.swap(tile->entity);
	tile = t;
}

//Returns the tile at the given coordinate
Tile& World::getTile(int x, int y)
{
	if (TileOutOfBounds(x, y)) return *Chunk::Impassable_Chunk()->data[0];
	auto& chunk = chunks[Coord(x / Chunk::size, y / Chunk::size, true)];
	
	return *chunk->data[(x % Chunk::size)*Chunk::size + (y % Chunk::size)];
}

Tile& World::getTile(const Coord& c)
{
	return getTile(c.x, c.y);
}

Chunk& World::getChunk(int x, int y)
{
	if (OutOfBounds(x, y)) return *Chunk::Impassable_Chunk();
	return *chunks[Coord(x / WorldSize, y % WorldSize, true)];
}

void World::Update()
{

	//Deal with updating things
	//TODO: Consolidate this with updating chunks... is spaghetti
	for (auto p : updateable)
	{
		p->Update();
	}

	timePressed++;


	//Deal with updating chunks

	static int selectedTile;
	int x, y;
	int index = 0;
	
	for each (Entity *p in players)
	{
		p->GetPosition(x, y);
		auto chunks = World::GetChunksAround(x,y);
		for (auto& c : *chunks)
		{
			if (c.second == Chunk::Impassable_Chunk()) continue;
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
std::unique_ptr<std::map<Coord, Chunk*>> World::GetChunksAround(int x, int y)
{
	auto ret = make_unique<std::map<Coord, Chunk*>>();
	for (int i = (x / Chunk::size) - RenderDistance; i < (x / Chunk::size) + RenderDistance; i++)
		for (int j = (y / Chunk::size) - RenderDistance; j < (y / Chunk::size) + RenderDistance; j++)
		{
			Coord chunk(i, j, true);
			if (OutOfBounds(i,j))
			{
				(*ret)[chunk] = (Chunk::Impassable_Chunk());
			}
			else if (World::chunks.find(chunk) == chunks.end())
			{
				World::chunks[chunk] = new Chunk(Chunk::chunk_generate_growth_sample(10, 4));
				(*ret)[chunk] = (World::chunks[chunk]);
			}
			else
				(*ret)[chunk] = (World::chunks[chunk]);
		}

	return ret;
}



//Draw the chunks in the render distance around the player
void World::Draw(int x, int y)
{
	int counts = 0;
	auto chunks = GetChunksAround(x, y);
	al_set_target_bitmap(display);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	ALLEGRO_TRANSFORM temp;
	int ex, ey;
	for each (auto& c in *chunks)
	{
		al_build_transform(&temp, c.first.x * Chunk::size * Tile::TILE_W, c.first.y * Chunk::size * Tile::TILE_H, 1, 1, 0);
		Push_Matrix(&temp);
		c.second->Draw();
		Pop_Matrix();
	}

	for each (auto& c in *chunks)
		for each (Tile *t in c.second->data)
		{
			if (t->selected) counts++;
			if (t->entity)
			{
				t->entity->GetPosition(ex, ey);
				al_build_transform(&temp, ex * Tile::TILE_W, ey * Tile::TILE_H, 1, 1, 0);
				Push_Matrix(&temp);
				t->entity->Draw();
				Pop_Matrix();
			}
		}
}

void World::Initialize()
{
	al_identity_transform(&transforms[0]);
	Tile::loadTiles();
}

void World::RegisterPlayer(Entity *p)
{
	try
	{
		int x, y;
		players.push_back(p);
		p->GetPosition(x, y);
		World::GetChunksAround(x, y);
		World::getTile(x, y).entity = std::unique_ptr<Entity>(p);
	}
	catch (const std::exception e)
	{
		std::cout << "Error registering player\n";
		throw e;
	}
}

void World::UnregisterPlayer(Entity *p) {
	throw new exception("Unimplemented function!\n");
}