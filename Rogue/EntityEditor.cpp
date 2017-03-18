#include "stdafx.h"
#include "EntityEditor.h"
#include "Entity.h"

EntityEditor::EntityEditor()
{
	posX = 1000;
	posY = 100;
}


EntityEditor::~EntityEditor()
{
}

void EntityEditor::Draw()
{
	auto line = posY;
	if (!selected) return;
	al_draw_filled_rectangle(posX, posY, posX + width, posY + height, al_map_rgba(30, 30, 30, 100));
	for (auto& str : selected->getNotes())
	{
		al_draw_text(font, al_map_rgb(255, 255, 255), posX, line + 10, 0, str.data());
		line += 20;
	}

	int cursorX = al_get_text_width(font, selected->getNotes()[0].data()) + posX;
	int cursorY = note * 20 + posY + 15;
	al_draw_line(cursorX, cursorY, cursorX, cursorY + 15, al_color_name("white"), 2);
}

void EntityEditor::Update()
{

}