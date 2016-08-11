#pragma once
#include "Tile.h"
#include "stdafx.h"

class Forest_Floor : public Tile
{
public:
	int RegisterImage();
	Forest_Floor();
	~Forest_Floor();
private:
	static int ID;
	
};

