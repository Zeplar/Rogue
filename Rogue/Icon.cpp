#include "stdafx.h"
#include "Icon.h"


Icon::Icon(coord& topLeft, coord& bottomRight, ALLEGRO_BITMAP *image) : Clickable(topLeft, bottomRight)
{
	this->image = image;
}


Icon::~Icon()
{
	std::cout << "Warning: Deleted icon but leaving its image.\n";
}

void Icon::Draw()
{
	al_draw_bitmap(image, topLeft.first, topLeft.second, 0);
}

void Icon::onClick()
{
	clickFunction();
}

void Icon::onMouseover()
{
	mouseFunction();
}