#pragma once
#include "Drawable.h"
class Clickable : public GUI::Drawable
{
public:
	Clickable(coord& topLeft, coord& bottomRight);
	~Clickable();

	virtual void Draw() = 0;

	//Called if isMouseover() returns true
	virtual void onClick() = 0;

	//Called if isMouseover() returns true
	virtual void onMouseover() = 0;

	virtual bool isMousover();

protected:
	coord topLeft;
	coord bottomRight;


};

