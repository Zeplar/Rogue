#pragma once
#include "Menu.h"
#include "Updateable.h"
#include "Selection.h"
#include <list>

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
	void Update(Selection& selection);

	//returns true if there is a currently selected tile
	bool tileActive();

	int posX;
	int posY;

private:
	Selection selection;
	int height;
	int width;
	int note;	//the note we're currently editing
	ALLEGRO_FONT *font;

	std::list<std::pair<Selection, std::vector<std::string>>> notes;
	void addNote(std::string note);
	std::vector<std::string>& getNotes();

	json serializeNotes();

};

