#pragma once
#include "Menu.h"
#include "Updateable.h"
class TileMenu :
	public Menu, public Updateable
{
public:
	TileMenu();
	~TileMenu();
	void Draw();
	//Check keyboard input and update text field if appropriate
	void Update();

	//Updates the selected tile; pass (-1,-1) to hide the menu
	void Update(coord& tile);

	//returns true if there is a currently selected tile
	bool tileActive();

	int posX;
	int posY;

private:
	coord tile;
	int height;
	int width;
	int note;	//the note we're currently editing
	ALLEGRO_FONT *font;

};

