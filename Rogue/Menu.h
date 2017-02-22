#pragma once
#include "GUI.h"
class Menu : public GUI::Drawable
{
public:
	Menu();
	~Menu();
	virtual void Draw();

	std::vector<Menu*> subMenus;
};

