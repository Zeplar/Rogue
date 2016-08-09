#pragma once
#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include "Tile.h"
class Player
{
public:
	Player();
	~Player();
	int x, y;
	float speed;
	ALLEGRO_BITMAP *image;

	float direction; //direction in radians

	int hp, mp;

	void Draw();
	void Move(bool *key);

	static Player* primaryPlayer;

private:
	static std::vector<Player*> players;
	float moveTimer = 0;

};

