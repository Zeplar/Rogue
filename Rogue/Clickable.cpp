#include "stdafx.h"
#include "Clickable.h"
#include "Camera.h"


Clickable::Clickable(Coord& topLeft, Coord& bottomRight)
{
	this->topLeft = topLeft;
	this->bottomRight = bottomRight;
}


Clickable::~Clickable()
{
}

bool Clickable::isMousover()
{
	Coord mouseCoords = Camera::mouseToScreen();
	
	bool horiz = topLeft.x < mouseCoords.x && mouseCoords.x < bottomRight.x;
	bool vert = topLeft.y < mouseCoords.y && mouseCoords.y < bottomRight.y;
	return horiz && vert;
}