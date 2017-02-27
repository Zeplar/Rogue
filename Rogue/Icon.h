#pragma once
#include "Clickable.h"
class Icon :
	public Clickable
{
public:
	Icon(coord& topLeft, coord& bottomRight, ALLEGRO_BITMAP *image);
	~Icon();
	void Draw();

	void onClick();

	void onMouseover();

	bool mask;

private:
	ALLEGRO_BITMAP *image;


};

