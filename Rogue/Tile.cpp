#include "stdafx.h"
#include "Tile.h"
#include <string>
#include <map>
#include "World.h"
#include <experimental\filesystem>
namespace fs = std::experimental::filesystem;

std::vector<ALLEGRO_BITMAP*> Tile::AllTiles;
std::vector<coord> Tile::currentlySelected;
std::vector<Tile> Tile::baseTiles;
Tile* Tile::impassable_tile = nullptr;
std::map<coord, std::vector<std::string>> Tile::notes;

void Tile::addNote(coord& tile, std::string note)
{
	notes[tile].push_back(note);
}

std::vector<std::string>& Tile::getNotes(coord& tile)
{
	return notes[tile];
}

Tile::Tile(ALLEGRO_BITMAP *raw)
{
	for (int i = 0; i < 8; i++)
		characteristics.push_back(false);

	std::unique_ptr<Entity> entity = nullptr;

	//Scale the image
	ALLEGRO_BITMAP *image = al_create_bitmap(TILE_W, TILE_H);
	al_set_target_bitmap(image);
	al_draw_scaled_bitmap(raw, 0, 0, al_get_bitmap_width(raw), al_get_bitmap_height(raw), 0, 0, TILE_W, TILE_H, 0);
	al_destroy_bitmap(raw);

	//Register the image
	id = (int)Tile::AllTiles.size();
	Tile::AllTiles.push_back(image);
	baseTiles.push_back(*this);
}


//Clone method
Tile::Tile(const Tile& t)
{
	id = t.id;
	characteristics = std::vector<bool>(t.characteristics);
	entity = nullptr;
}

Tile::Tile()
{
	throw new std::exception("Tile created with no arguments");
}

Tile::~Tile()
{
}

const std::vector<bool>& Tile::Characteristics()
{
	return characteristics;
}

void Tile::SetCharacteristic(int characteristic, bool setting)
{
	characteristics[characteristic] = setting;
}

void Tile::Draw()
{
	if (id == -1)
	{
		al_draw_bitmap(Tile::AllTiles[1], 0, 0, 0);
		return;
	}
	if (AllTiles[id] == NULL)
	{
		std::cerr << "Error: Null tile bitmap.\n";
		throw std::exception("Error: Null tile bitmap.\n");
	}
	al_draw_bitmap(Tile::AllTiles[id], 0, 0, 0);
	if (selected)
	{
		al_draw_tinted_bitmap(Tile::AllTiles[id], al_map_rgb(200, 200, 200), 0, 0, 0);
	}
}


void Tile::select(coord t)
{
	auto &tile = World::getTile(t);
	if (tile.id != -1)
	{
		currentlySelected.push_back(t);
		tile.selected = true;
	}
}

void Tile::loadTiles()
{
	const char* path = R"(C:\Users\Joshua\Documents\Visual Studio 2015\Projects\Rogue\Rogue\Rogue\tiles)";
	std::map<std::string, std::vector<bool>> tileMapping;

	tileMapping[std::string("Forest_Tree.bmp")] = { false, true, false, false };
	tileMapping[std::string("Forest_Floor.bmp")] = { true, true, false, false };

	try {
		for (auto& p : fs::directory_iterator(path))
		{
			if (p.path().extension() != std::string(".bmp")) continue;
			Tile(al_load_bitmap(p.path().string().data()));
			if (tileMapping.find(p.path().filename().string()) != tileMapping.end())
			{
				baseTiles.back().characteristics = tileMapping[p.path().filename().string()];
			}
		}
		impassable_tile = new Tile(baseTiles[1]);
		impassable_tile->id = -1;
		impassable_tile->SetCharacteristic(Characteristic::Flyable, false);
	}
	catch (const std::exception& e)
	{
		std::cout << "Error in TerrainMenu::loadTiles";
		throw e;
	}
	std::cout << "Loaded " << baseTiles.size() << " terrain tiles.\n";
}
