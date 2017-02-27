#include "stdafx.h"
#include "Clickable.h"
#include "Camera.h"


Clickable::Clickable(coord& topLeft, coord& bottomRight)
{
	this->topLeft = topLeft;
	this->bottomRight = bottomRight;
}


Clickable::~Clickable()
{
}

bool Clickable::isMousover()
{
	coord mouseCoords;
	Camera::mouseToScreen(mouseCoords.first, mouseCoords.second);

	std::cout << "Mouse: " << mouseCoords.first << "," << mouseCoords.second;
	std::cout << "   Icon: " << topLeft.first << "," << topLeft.second << "-" << bottomRight.first << "," << bottomRight.second << "\n";
	
	bool horiz = topLeft.first < mouseCoords.first && mouseCoords.first < bottomRight.first;
	bool vert = topLeft.second < mouseCoords.second && mouseCoords.second < bottomRight.second;
	return horiz && vert;
}