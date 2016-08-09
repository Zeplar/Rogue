#include "stdafx.h"
#include "Player.h"
#include "World.h"
#include <algorithm>



const int player_width = 10;
const int player_height = 20;
const int TIME_TO_MOVE = 20;

std::vector<Player*> Player::players = std::vector<Player*>();
Player* Player::primaryPlayer = NULL;

Player::Player()
{
	speed = 20;
	x = y = 8;
	image = al_create_bitmap(Tile::TILE_W, Tile::TILE_H);
	al_set_target_bitmap(image);
	al_draw_filled_triangle(1, 1, player_width, 1, player_width / 2.0, player_height, al_map_rgb(255, 0, 0));
	al_draw_triangle(0, 1, player_width, 1, player_width / 2.0, player_height, al_map_rgb(255, 255, 255), 1);
	players.push_back(this);
}

void Player::Draw()
{
	al_draw_rotated_bitmap(image, player_width / 2.0, player_height / 2.0,
		x * Tile::TILE_W + Tile::TILE_W/2, 
		y * Tile::TILE_H + Tile::TILE_H/2, 
		direction + M_PI, 0);
}

void Player::Move(bool *key)
{
	int tempX = x;
	int tempY = y;
	if (key[ALLEGRO_KEY_DOWN] || key[ALLEGRO_KEY_UP] || key[ALLEGRO_KEY_LEFT] || key[ALLEGRO_KEY_RIGHT])
		moveTimer++;

	if (moveTimer >= speed)
	{
		moveTimer = 0;
		direction = (key[ALLEGRO_KEY_RIGHT] - key[ALLEGRO_KEY_LEFT]) * M_PI_2 + key[ALLEGRO_KEY_DOWN] * M_PI;
		tempX = key[ALLEGRO_KEY_RIGHT] - key[ALLEGRO_KEY_LEFT] + x;
		tempY = key[ALLEGRO_KEY_DOWN] - key[ALLEGRO_KEY_UP] + y;

		if (World::getTile(tempX, tempY)->isWalkable())
		{
			x = tempX; y = tempY;
		}
	}



}


Player::~Player()
{
	al_destroy_bitmap(image);
}
