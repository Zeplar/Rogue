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
	Coord topLeft(posX, posY, false);

	for (auto& tile : Tile::AllTiles)
	{
		std::cout << "Loaded icon into terrainmenu\n";
		icons.push_back(new Icon(topLeft, Coord(topLeft.x + Tile::TILE_W, topLeft.y + Tile::TILE_H, false), tile));

		topLeft.x += Tile::TILE_W;
		if (topLeft.x > width)
		{
			topLeft.x = 0;
			topLeft.y += Tile::TILE_H;
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

	if (!World::mouseEvent) return;

	if (World::mouseEvent.x > posX + width || World::mouseEvent.y > posY + height)
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
	World::mouseEvent = Coord();
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
