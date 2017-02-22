#include "stdafx.h"
#include "Menu.h"


Menu::Menu()
{
}


Menu::~Menu()
{
}

void Menu::Draw()
{
	for (auto &menu : subMenus)
		menu->Draw();
}