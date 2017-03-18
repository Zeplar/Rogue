#pragma once
#include "Menu.h"
class EntityEditor :
	public Menu
{
public:
	EntityEditor();
	~EntityEditor();
	void Draw();
	void Update();
	Entity* selected;

private:
	int posX, posY, height, width;
	ALLEGRO_FONT *font;
	int note;


};

