#pragma once
#include "Menu.h"
class TileMenu :
	public Menu
{
public:
	TileMenu();
	~TileMenu();
	void Draw();

	//Updates the selected tile; pass nullptr to hide the menu
	void Update(coord& tile);

	int posX;
	int posY;

private:
	coord tile;
	int height;
	int width;
	ALLEGRO_FONT *font;

};

