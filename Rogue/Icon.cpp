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
	if (mask) al_draw_filled_rectangle(topLeft.first, topLeft.second, bottomRight.first, bottomRight.second, al_map_rgba_f(0,0,0,.3));
}

void Icon::onClick()
{
}
void Icon::onMouseover()
{

}