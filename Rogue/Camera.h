#pragma once
#include "GUI.h"
class Camera
{
public:
	Camera();
	~Camera();

	//Returns the screen coordinates of the given tile coordinates
	static Coord tileToScreen(const Coord & tile);

	static Coord coordToScreen(const Coord & c);

	//Returns the screen coordinates of the map cursor
	static Coord mouseToScreen();

	//Returns the world coordinates (tile coordinate) of the given screen coordinate
	static Coord screenToTile(const Coord & c);

	static ALLEGRO_TRANSFORM *current_transform;

	static Coord mouseoverTile();

	//Converts the tile coordinates into a rectangle on screen
	static void selectionRectangle(Coord & topLeft, Coord & bottomRight);

	static std::vector<Coord> mouseoverTiles();
	
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

