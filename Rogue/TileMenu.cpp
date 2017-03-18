#include "stdafx.h"
#include "TileMenu.h"
#include "Tile.h"
#include "Camera.h"
#include "World.h"
#include "Drawable.h"

TileMenu::TileMenu()
{
	height = 200;
	width = 400;
	posX = al_get_display_width(al_get_current_display()) / 3;
	posY = 10;
	font = al_load_ttf_font("Times.ttf", 24, 0);
	note = 0;
	selection = Selection();

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

void TileMenu::Update(Selection& selection)
{
	if (this->selection == selection) return;
	if (this->selection && getNotes().size() == 1 && getNotes()[0].length() == 0)
	{
		for (auto& n : notes)
		{
			if (n.first == this->selection)
			{
				notes.remove(n);
				break;
			}
		}
	}
	this->selection = selection;
	note = 0;
	if (!selection) return;
	if (getNotes().size() == 0) getNotes().push_back(std::string());
}

bool TileMenu::tileActive()
{
	return bool(selection);
}

void TileMenu::Draw()
{
	auto line = posY;
	if (!tileActive()) return;
	al_draw_filled_rectangle(posX, posY, posX+width, posY+height, al_map_rgba(30,30,30,100));
	for (auto& str : getNotes())
	{
		al_draw_text(font, al_map_rgb(255, 255, 255), posX, line + 10, 0, str.data());
		line += 20;
	}

	int cursorX = al_get_text_width(font, getNotes()[note].data()) + posX;
	int cursorY = note * 20 + posY + 15;
	al_draw_line(cursorX, cursorY, cursorX, cursorY + 15, al_color_name("white"), 2);

	Selection mouseoverSelection(Camera::mouseoverTile(), Camera::mouseoverTile());

	if (World::key[ALLEGRO_KEY_TAB])
	{
		mouseoverSelection = Selection::getScreen();
	}

	for (auto& s : notes)
	{
		if (s.first.overlaps(mouseoverSelection))
			s.first.Draw();
	}
	
}


json TileMenu::serializeNotes()
{
	json j;
	for (auto &p : notes)
	{
		//TODO
	}
	return j;
}

void TileMenu::addNote(std::string note)
{
	auto& str_vec = getNotes();
	str_vec.push_back(note);
}

std::vector<std::string>& TileMenu::getNotes()
{
	if (!selection) throw std::exception();

	for (auto& n : notes)
	{
		if (n.first == selection)
		{
			return n.second;
		}
	}
	notes.push_back(std::pair<Selection, std::vector<std::string>>(selection, std::vector<std::string>()));
	return notes.back().second;
}

void TileMenu::Update()
{
	Update(Selection(Tile::currentlySelected));



	if (World::key[ALLEGRO_KEY_ESCAPE])
	{
		Update(Selection());
		return;
	}

	else if (!tileActive() || World::timePressed > 0) return;

	auto& vec = getNotes();
	if (vec.size() < 1) vec.push_back(std::string());
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

	else if (World::key[ALLEGRO_KEY_TAB]) return;

	else if (World::keyPress != 0)
	{
		n.push_back(World::keyPress);
	}
}