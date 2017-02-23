#include "stdafx.h"
#include "Clickable.h"
#include "Camera.h"


Clickable::Clickable(coord& topLeft, coord& bottomRight)
{
	topLeft = topLeft;
	bottomRight = bottomRight;
}


Clickable::~Clickable()
{
}

bool Clickable::isMousover()
{
	coord mouseCoords;
	Camera::mouseToScreen(mouseCoords.first, mouseCoords.second);
	
	bool horiz = topLeft.first < mouseCoords.first < bottomRight.first;
	bool vert = topLeft.second < mouseCoords.second < bottomRight.second;
	return horiz && vert;
}