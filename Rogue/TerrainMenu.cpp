#include "stdafx.h"
#include "TerrainMenu.h"
#include "Tiles.h"
namespace fs = std::experimental::filesystem;
TerrainMenu::TerrainMenu()
{
	posX = 0;
	posY = 0;
	height = 500;
	width = 200;
	selected = -1;
	Update(-1);
}

TerrainMenu::~TerrainMenu()
{
}

void TerrainMenu::setTiles()
{
	if (selected == -1) return;
	for (auto &p : Tile::currentlySelected)
		World::setTile(p, new Tile(Tile::baseTiles[selected]));
}

void TerrainMenu::checkInput()
{
	if (World::key[ALLEGRO_KEY_SPACE])
		selected = -1;

	if (!std::get<0>(World::mouseEvent)) return;

	int x = std::get<1>(World::mouseEvent);
	int y = std::get<2>(World::mouseEvent);

	if (x > posX + width || y > posY + height)
	{
		return;
	}
	x -= posX; y -= posY;	//Normalize x,y coordinates in reference to the menu

	int tileNum = (y / tileSide) * (width / tileSide)
		+ (x / tileSide);

	if (tileNum >= Tile::baseTiles.size()) return;

	selected = tileNum;
	std::get<0>(World::mouseEvent) = false;
	setTiles();
}

void TerrainMenu::Update(int selected)
{
	auto display = al_get_target_bitmap();
	int x = 0;
	int y = 0;

	if (image != nullptr) al_destroy_bitmap(image);
	image = al_create_bitmap(width, height);
	al_set_target_bitmap(image);
	al_draw_filled_rectangle(0, 0, width, height, al_map_rgba(50, 50, 50, 30));
	al_draw_rectangle(0, 0, width, height, al_color_name("red"), 2);

	for (int i = 0; i < Tile::baseTiles.size(); i++) {
		if (x >= width) {
			x = 0;
			y += tileSide;
		}
		if (selected == i) 	al_draw_tinted_bitmap(Tile::AllTiles[selected], al_map_rgb(200, 200, 200), x, y, 0);
		else	al_draw_bitmap(Tile::AllTiles[i], x, y, 0);
		al_draw_rectangle(x, y, x + tileSide, y + tileSide, al_map_rgb(20, 20, 200), 1);
		x += tileSide;
	}

	al_set_target_bitmap(display);

}

void TerrainMenu::Draw() 
{
	checkInput();
	if (selected != -1)
	{
		Update(selected);
	}
	al_draw_bitmap(image, 0, 0, 0);
}
