#pragma once
#include "Menu.h"
#include "World.h"
#include "Camera.h"
#include <experimental\filesystem>
#include "Icon.h"

class TerrainMenu :
	public Menu
{
public:
	TerrainMenu();
	~TerrainMenu();
	void checkInput();	//Returns the index of the selected tile or -1 if no tile was selected
	void Draw();
	int posX;
	int posY;
	int height;
	int width;

private:
	std::vector<Icon*> icons;
	const int tileSide = 30;
	int selected;	//Index of the currently selected tile
	void setTiles();
	void loadTiles();

};

