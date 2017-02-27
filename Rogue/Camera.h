#pragma once
#include "GUI.h"
class Camera
{
public:
	Camera();
	~Camera();

	static coord coordToScreen(const coord & c);

	//Sets (x,y) to the screen coordinates of the map cursor
	static void mouseToScreen(int & x, int & y);

	//Returns the world coordinates (tile coordinate) of the given screen coordinate
	static coord mouseoverTile(coord & c);
	static ALLEGRO_TRANSFORM *current_transform;

	static coord mouseoverTile();

	static void selectionRectangle(coord & topLeft, coord & bottomRight);

	static std::vector<coord> mouseoverTiles();
	
	ALLEGRO_TRANSFORM camera_transform;
	void Transform_Camera(float x, float y);

	static void drawScreen();

	static void checkKeys();
	//Draw the selection rectangle
	static void drawSelection();
	//Select all tiles highlighted
	static void selectTiles();

	static std::vector<GUI::Drawable*> screen;

private:
	bool clear_selection;

};

