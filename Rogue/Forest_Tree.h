#pragma once
#include "Tile.h"
#include "stdafx.h"

class Forest_Tree :
	public Tile
{
public:
	Forest_Tree();
	~Forest_Tree();
	bool isWalkable();
	int RegisterImage();
private:
	static int ID;
};

