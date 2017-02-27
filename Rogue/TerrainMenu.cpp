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

	loadTiles();

}

TerrainMenu::~TerrainMenu()
{
}

void TerrainMenu::loadTiles()
{
	coord topLeft(posX, posY);

	for (auto& tile : Tile::AllTiles)
	{
		std::cout << "Loaded icon into terrainmenu\n";
		icons.push_back(new Icon(topLeft, coord(topLeft.first + Tile::TILE_W, topLeft.second + Tile::TILE_H), tile));

		topLeft.first += Tile::TILE_W;
		if (topLeft.first > width)
		{
			topLeft.first = 0;
			topLeft.second += Tile::TILE_H;
		}
	}
}

void TerrainMenu::setTiles()
{
	if (selected == -1) return;
	for (auto &p : Tile::currentlySelected)
		World::setTile(p, new Tile(Tile::baseTiles[selected]));
}

void TerrainMenu::checkInput()
{
	if (World::key[ALLEGRO_KEY_ESCAPE])
		selected = -1;

	if (!std::get<0>(World::mouseEvent)) return;

	int x = std::get<1>(World::mouseEvent);
	int y = std::get<2>(World::mouseEvent);

	if (x > posX + width || y > posY + height)
	{
		return;
	}
	int i = 0;
	for (auto icon : icons)
	{
		if (icon->isMousover())
		{
			selected = i;
			break;
		}
		i++;
	}
	std::get<0>(World::mouseEvent) = false;
	setTiles();
}

void TerrainMenu::Draw() 
{
	al_draw_filled_rectangle(0, 0, width, height, al_map_rgba(50, 50, 50, 30));
	al_draw_rectangle(0, 0, width, height, al_color_name("red"), 2);
	
	for (auto icon : icons) {
		icon->Draw();
		icon->mask = false;
	}

	checkInput();
	if (selected != -1)
	{
		icons[selected]->mask = true;
	}
}
