#include "stdafx.h"
#include "GUI.h"
#include "Tile.h"


GUI::GUI()
{
}


GUI::~GUI()
{
}


GUI::StatusBar::StatusBar(const int & x, const int & y, const int & var, const int & max_value, ALLEGRO_COLOR color) : x(x), y(y), var(var), max(max_value), color(color)
{
}

void GUI::StatusBar::Draw()
{
	int length = var / max;

	al_draw_filled_rectangle(0, 0, length, 8, color);
	al_draw_rectangle(0, 0, Tile::TILE_W, 8, al_color_name("white"), 3);
}
