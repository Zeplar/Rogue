#include "stdafx.h"
#include "Tile.h"
#include <string>
#include <map>
#include "World.h"
#include <experimental\filesystem>
#include <sstream>
#include <fstream>

namespace fs = std::experimental::filesystem;

std::vector<ALLEGRO_BITMAP*> Tile::AllTiles;
std::vector<Coord> Tile::currentlySelected;
std::vector<Tile> Tile::baseTiles;
Tile* Tile::impassable_tile = nullptr;
std::vector<std::string> Tile::CharacteristicNames;
std::vector<std::string> Tile::TileNames;

Tile::Tile(int id) : id(id)
{
	characteristics = baseTiles[id].characteristics;
	entity = nullptr;
}

Tile::Tile(ALLEGRO_BITMAP *raw) : id(Tile::AllTiles.size())
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
	Tile::AllTiles.push_back(image);
	baseTiles.push_back(*this);
}


//Clone method
Tile::Tile(const Tile& t) : id(t.id)
{
	characteristics = std::vector<bool>(t.characteristics);
	entity = nullptr;
}

Tile::Tile() : id(-1)
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

void Tile::SetCharacteristic(const char* c, bool setting)
{
	for (int i = 0; i < CharacteristicNames.size(); i++)
	{
		if (CharacteristicNames[i] == c)
		{
			characteristics[i] = setting;
			return;
		}
	}
	std::cout << "Wasn't able to find a characteristic \"" << c << "\"\n";
}

bool Tile::getCharacteristic(const char * c)
{
	for (int i = 0; i < CharacteristicNames.size(); i++)
	{
		if (CharacteristicNames[i] == c)
		{
			return characteristics[i];
		}
	}
	std::cout << "Couldn't find a characteristic: \"" << c << "\"\n";
	throw new std::exception();
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


void Tile::select(Coord& t)
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
	CharacteristicNames = parseSaveTileCharacteristics();

	std::cout << "Parsed characteristics: \n";
	for (auto& str : CharacteristicNames)
		std::cout << str << "\n";

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
		impassable_tile->SetCharacteristic("Flyable", false);
	}
	catch (const std::exception& e)
	{
		std::cout << "Error in TerrainMenu::loadTiles";
		throw e;
	}
	std::cout << "Loaded " << baseTiles.size() << " terrain tiles.\n";

}

std::vector<std::string> Tile::parseSaveTileCharacteristics()
{
	//all this just to read the file into a string... ew?
	const char* path = R"(C:\Users\Joshua\Documents\Visual Studio 2015\Projects\Rogue\Rogue\Rogue\tiles\tilemap.txt)";
	std::ifstream f(path);
	std::stringstream stream;
	stream << f.rdbuf();
	std::string unparsed = stream.str();
	
	int start = unparsed.find("=") + 2;
	int end = unparsed.find("TILES");
	auto section = unparsed.substr(start, end - start);

	auto tokens = split(section, std::string(","));
	for (auto& str : tokens)
		str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
	return tokens;
}


std::vector<std::string> Tile::parseSaveTileMap()
{
	//all this just to read the file into a string... ew?
	const char* path = R"(C:\Users\Joshua\Documents\Visual Studio 2015\Projects\Rogue\Rogue\Rogue\tiles\tilemap.txt)";
	std::ifstream f(path);
	std::stringstream stream;
	stream << f.rdbuf();
	std::string unparsed = stream.str();

	int start = unparsed.find("TILES =") + 7;
	auto section = unparsed.substr(start);

	auto tokens = split(section, std::string("\n"));
	for (auto& str : tokens)
		str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
	return tokens;
}

std::vector<std::string> Tile::split(const std::string& str, const std::string& delim)
{
	std::vector<std::string> tokens;
	size_t prev = 0, pos = 0;
	do
	{
		pos = str.find(delim, prev);
		if (pos == std::string::npos) pos = str.length();
		std::string token = str.substr(prev, pos - prev);
		if (!token.empty()) tokens.push_back(token);
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}