#pragma once
#include "stdafx.h"
#include "Entity.h"

//Individual tiles contain information about moveability and entities present on that tile
//At present it's assumed that no more than one entity can occupy a single tile
class Tile
{
	friend class World;


public:
	static void addNote(coord & tile, std::string note);
	static std::vector<std::string>& getNotes(coord & tile);
	Tile(int id);
	Tile(ALLEGRO_BITMAP* raw);
	Tile(const Tile& t);
	Tile();
	~Tile();
	enum Characteristic { Walkable, Flyable, Swimmable, SpawnsEnemies };

	const std::vector<bool>& Characteristics();
	void SetCharacteristic(int Characteristic, bool setting);
	void Draw();

	static void select(coord t);

	static void loadTiles();

	static const int TILE_W = 30;
	static const int TILE_H = 30;
	std::unique_ptr<Entity> entity;
	static std::vector<coord> currentlySelected;

	bool selected;

	static std::vector<Tile> baseTiles;
	static std::vector<ALLEGRO_BITMAP*> AllTiles;

	static Tile* impassable_tile;

	static std::map<coord, std::vector<std::string>> notes;

	const int id;

	static json serializeNotes();

protected:
	std::vector<bool> characteristics;
};

