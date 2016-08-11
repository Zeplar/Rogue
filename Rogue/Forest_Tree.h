#pragma once
#include "Tile.h"
#include "stdafx.h"

class Forest_Tree :
	public Tile
{
public:
	Forest_Tree();
	~Forest_Tree();
	int RegisterImage();
private:
	static int ID;
};

