#include "stdafx.h"
#include "Player.h"
#define _USE_MATH_DEFINES
#include <math.h>

const int player_width = 10;
const int player_height = 20;

Player::Player()
{
	dx = dy = 0;
	x = y = 200;
	image = al_create_bitmap(player_width, player_height);
	al_set_target_bitmap(image);
	al_draw_filled_triangle(0, 1, player_width, 1, player_width / 2.0, player_height, al_map_rgb(255, 0, 0));
	al_draw_triangle(0, 1, player_width, 1, player_width / 2.0, player_height, al_map_rgb(255, 255, 255), 1);
}

void Player::Draw()
{
	al_draw_rotated_bitmap(image, player_width / 2.0, player_height / 2.0, x, y, direction + M_PI, 0);
}

void Player::Move(bool *key)
{
	if (key[ALLEGRO_KEY_UP])
	{
		y -= 1;
		direction = 0;
	}
	if (key[ALLEGRO_KEY_DOWN])
	{
		y += 1;
		direction = M_PI;
	}
	if (key[ALLEGRO_KEY_LEFT])
	{
		x -= 1;
		direction = 3.0 * M_PI / 2;
	}
	if (key[ALLEGRO_KEY_RIGHT])
	{
		x += 1;
		direction = M_PI / 2;
	}
}


Player::~Player()
{
	al_destroy_bitmap(image);
}
