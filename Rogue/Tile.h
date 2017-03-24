#pragma once
#include "stdafx.h"
#include "Entity.h"

//Individual tiles contain information about moveability and entities present on that tile
//At present it's assumed that no more than one entity can occupy a single tile
class Tile
{
	friend class World;

public:
	Tile(int id);
	Tile(ALLEGRO_BITMAP* raw);
	Tile(const Tile& t);
	Tile();
	~Tile();

	static std::vector<std::string> CharacteristicNames;
	static std::vector<std::string> TileNames;

	const std::vector<bool>& Characteristics();
	void SetCharacteristic(int Characteristic, bool setting);
	void SetCharacteristic(const char * c, bool setting);
	bool getCharacteristic(const char* c);
	void Draw();

	static void select(Coord& t);

	static void loadTiles();

	static const int TILE_W = 30;
	static const int TILE_H = 30;
	std::unique_ptr<Entity> entity;
	static std::vector<Coord> currentlySelected;

	bool selected;

	static std::vector<Tile> baseTiles;
	static std::vector<ALLEGRO_BITMAP*> AllTiles;

	static Tile* impassable_tile;

	const int id;

protected:
	std::vector<bool> characteristics;

private:
	static std::vector<std::string> parseSaveTileCharacteristics();
	static std::vector<std::string> split(const std::string & str, const std::string & delim);
	static std::vector<std::string> parseSaveTileMap();
};

