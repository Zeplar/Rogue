#include "stdafx.h"
#include "SaveFile.h"
#include "World.h"
#include "Tile.h"
#include "Entity.h"
#include <iostream>
#include <fstream>


SaveFile::SaveFile(const std::string& fileName)
{
	json save;
	save["chunks"] = World::serializeTiles();
	save["notes"] = Tile::serializeNotes();
	
	std::ofstream o(fileName);
	o << save;
	o.close();
}

void SaveFile::loadFile(const std::string& fileName)
{
	std::ifstream f(fileName);
	json save(f);
	World::loadChunks(save["chunks"]);
}


SaveFile::~SaveFile()
{
}
