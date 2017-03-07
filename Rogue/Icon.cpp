#include "stdafx.h"
#include "Icon.h"


Icon::Icon(Coord& topLeft, Coord& bottomRight, ALLEGRO_BITMAP *image) : Clickable(topLeft, bottomRight)
{
	this->image = image;
}


Icon::~Icon()
{
	std::cout << "Warning: Deleted icon but leaving its image.\n";
}

void Icon::Draw()
{
	al_draw_bitmap(image, topLeft.x, topLeft.y, 0);
	if (mask) al_draw_filled_rectangle(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y, al_map_rgba_f(0,0,0,.3));
}

void Icon::onClick()
{
}
void Icon::onMouseover()
{

}