#pragma once
#include "Drawable.h"
class Clickable : public GUI::Drawable
{
public:
	Clickable(Coord& topLeft, Coord& bottomRight);
	~Clickable();

	virtual void Draw() = 0;

	//Called if isMouseover() returns true
	virtual void onClick() = 0;

	//Called if isMouseover() returns true
	virtual void onMouseover() = 0;

	virtual bool isMousover();

protected:
	Coord topLeft;
	Coord bottomRight;


};

