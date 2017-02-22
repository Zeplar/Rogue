#include "stdafx.h"
#include "TileMenu.h"
#include "Tile.h"
#include "Camera.h"

TileMenu::TileMenu()
{
	height = 200;
	width = 400;
	posX = al_get_display_width(al_get_current_display()) / 3;
	posY = 10;
	font = al_load_ttf_font("Times.ttf", 24, 0);
	if (!font)
	{
		std::cout << "Failed to load font.\n";
		throw std::exception("Failed to load font.");
	}

}


TileMenu::~TileMenu()
{
}

void TileMenu::Update(coord& tile)
{
	this->tile = tile;
}

void TileMenu::Draw()
{

	if (Tile::currentlySelected.size() == 0) return;
	if (Tile::currentlySelected.size() == 1) Update(Tile::currentlySelected[0]);
	al_draw_filled_rectangle(posX, posY, posX+width, posY+height, al_map_rgba(30,30,30,100));
	for (auto& str : Tile::getNotes(tile))
	{
		al_draw_text(font, al_map_rgb(255, 255, 255), posX, posY + 10, 0, str.data());
	}
	
}