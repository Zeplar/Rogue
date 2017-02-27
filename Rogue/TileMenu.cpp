#include "stdafx.h"
#include "TileMenu.h"
#include "Tile.h"
#include "Camera.h"
#include "World.h"

TileMenu::TileMenu()
{
	height = 200;
	width = 400;
	posX = al_get_display_width(al_get_current_display()) / 3;
	posY = 10;
	font = al_load_ttf_font("Times.ttf", 24, 0);
	note = 0;
	if (!font)
	{
		std::cout << "Failed to load font.\n";
		throw std::exception("Failed to load font.");
	}
	World::updateable.push_back(this);
}


TileMenu::~TileMenu()
{
}

void TileMenu::Update(coord& tile)
{
	this->tile = tile;
	note = 0;
	if (Tile::notes[tile].size() == 0)
	{
		Tile::addNote(tile, std::string());
	}
}

bool TileMenu::tileActive()
{
	return (tile.first >= 0);
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

void TileMenu::Update()
{
	if (World::key[ALLEGRO_KEY_ESCAPE]) Update(coord(-1, -1));

	else if (!tileActive()) return;

	else if (World::timePressed == 0 && World::keyPress != 0)
	{
		Tile::getNotes(tile)[note].push_back(World::keyPress);
		std::cout << "Key is " << World::keyPress << "\n";
		std::cout << Tile::getNotes(tile)[note] << "\n";

	}
}