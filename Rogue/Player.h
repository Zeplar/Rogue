#pragma once
#include <allegro5\bitmap.h>
#include <allegro5\allegro_primitives.h>
class Player
{
public:
	Player();
	~Player();
	int x, y;
	float dx, dy;
	ALLEGRO_BITMAP *image;

	float direction; //direction in radians

	int hp, mp;

	void Draw();
	void Move(bool *key);

};

