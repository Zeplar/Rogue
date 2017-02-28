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
	tile = coord(-1, -1);
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
	auto line = posY;
	if (!tileActive()) return;
	al_draw_filled_rectangle(posX, posY, posX+width, posY+height, al_map_rgba(30,30,30,100));
	for (auto& str : Tile::getNotes(tile))
	{
		al_draw_text(font, al_map_rgb(255, 255, 255), posX, line + 10, 0, str.data());
		line += 20;
	}

	int cursorX = al_get_text_width(font, Tile::getNotes(tile)[note].data()) + posX;
	int cursorY = note * 20 + posY + 15;
	al_draw_line(cursorX, cursorY, cursorX, cursorY + 15, al_color_name("white"), 2);
	
}

void TileMenu::Update()
{
	if (Tile::currentlySelected.size() == 1 && Tile::currentlySelected[0] != tile) Update(Tile::currentlySelected[0]);

	if (World::key[ALLEGRO_KEY_ESCAPE])
	{
		Update(coord(-1, -1));
		return;
	}

	else if (!tileActive() || World::timePressed > 0) return;

	auto& vec = Tile::getNotes(tile);
	auto& n = vec[note];

	if (World::key[ALLEGRO_KEY_ENTER])
	{
		note++;
		if (vec.size() <= note)
			vec.push_back(std::string());
		return;
	}
	

	if (World::key[ALLEGRO_KEY_BACKSPACE])
	{
		if (!n.empty())
			n.pop_back();
		else if (note == 0) return;

		else if (vec.size() > 1)
		{
			vec.erase(vec.begin() + note);
			note--;
		}
	}

	else if (World::key[ALLEGRO_KEY_DOWN])
	{
		note = std::min(note + 1, (int)vec.size()-1);
	}
	else if (World::key[ALLEGRO_KEY_UP])
		note = std::max(note - 1, 0);

	else if (World::keyPress != 0)
	{
		n.push_back(World::keyPress);
	}
}