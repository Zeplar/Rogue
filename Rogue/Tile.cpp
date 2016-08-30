#include "stdafx.h"
#include "Tile.h"
#include <string>

int Tile::numTiles = 0;
std::vector<ALLEGRO_BITMAP*> Tile::AllTiles(32);

Tile::Tile()
{
	for (int i = 0; i < 8; i++)
		characteristics.push_back(false);

	std::unique_ptr<Entity> entity = nullptr;
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
	if (AllTiles[TileID] == NULL)
	{
		std::cerr << "Error: Null tile bitmap.\n";
		return;
	}
	al_draw_bitmap(Tile::AllTiles[TileID], 0, 0, 0);
}

int Tile::RegisterImage(const char TileName[])
{
	std::string filename = "C:/Users/JHep/Documents/Visual Studio 2015/Projects/Rogue/Rogue/Rogue/tiles/";
	filename.append(TileName);

	ALLEGRO_BITMAP *raw = al_load_bitmap(filename.c_str());
	if (raw == NULL) fprintf(stderr, "Error: Bitmap failed to load\n");
	ALLEGRO_BITMAP *image = al_create_bitmap(TILE_W, TILE_H);
	al_set_target_bitmap(image);
	al_draw_scaled_bitmap(raw, 0, 0, al_get_bitmap_width(raw), al_get_bitmap_height(raw), 0, 0, TILE_W, TILE_H, 0);
	al_destroy_bitmap(raw);

	//Register the image
	Tile::AllTiles[numTiles] = image;
	return Tile::numTiles++;
}

int Tile::RegisterImage(ALLEGRO_BITMAP * image)
{
	Tile::AllTiles[numTiles] = image;
	return Tile::numTiles++;
}
