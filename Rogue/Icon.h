#pragma once
#include "Clickable.h"
class Icon :
	public Clickable
{
public:
	Icon(coord& topLeft, coord& topRight, ALLEGRO_BITMAP *image);
	~Icon();
	void Draw();
	void onClick();
	void onMouseover();

	void (*clickFunction)();
	void (*mouseFunction)();

private:
	ALLEGRO_BITMAP *image;

};

