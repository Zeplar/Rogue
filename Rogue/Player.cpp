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
	x = y = 0;
	MovementType = Tile::Characteristics::Flyable;

	image = al_create_bitmap(Tile::TILE_W, Tile::TILE_H);
	al_set_target_bitmap(image);
	al_draw_filled_triangle(1, 1, player_width, 1, player_width / 2.0, player_height, al_map_rgb(255, 0, 0));
	al_draw_triangle(0, 1, player_width, 1, player_width / 2.0, player_height, al_map_rgb(255, 255, 255), 1);
	
	al_identity_transform(&camera_transform);

	players.push_back(this);
}

void Player::Draw()
{
	al_draw_rotated_bitmap(image, player_width / 2.0, player_height / 2.0,
		x * Tile::TILE_W + Tile::TILE_W/2, 
		y * Tile::TILE_H + Tile::TILE_H/2, 
		direction + M_PI, 0);

	Transform_Camera();
}

void Player::Move(bool *key)
{
	float tempX = x;
	float tempY = y;
	if (key[ALLEGRO_KEY_DOWN] || key[ALLEGRO_KEY_UP] || key[ALLEGRO_KEY_LEFT] || key[ALLEGRO_KEY_RIGHT])
		moveTimer++;

	if (moveTimer >= speed)
	{
		moveTimer = 0;
		direction = (key[ALLEGRO_KEY_RIGHT] - key[ALLEGRO_KEY_LEFT]) * M_PI_2 + key[ALLEGRO_KEY_DOWN] * M_PI;
		tempX = key[ALLEGRO_KEY_RIGHT] - key[ALLEGRO_KEY_LEFT] + x;
		tempY = key[ALLEGRO_KEY_DOWN] - key[ALLEGRO_KEY_UP] + y;

		if (World::getTile(tempX, tempY)->Characteristics()[MovementType])
		{
			x = tempX; y = tempY;
		}
	}

}

void Player::Transform_Camera()
{
	float x = Player::x * Tile::TILE_W; float y = Player::y * Tile::TILE_H;		//Screen x,y coordinates
	float w = al_get_display_width(al_get_current_display());		//Screen width
	float h = al_get_display_height(al_get_current_display());		//Screen height

	al_transform_coordinates(&camera_transform, &x, &y);
	if (x < .33*w || x > .66*w) al_translate_transform(&camera_transform, (.5*w - x) * 0.01, 0);
	if (y < .33*h || y > .66*h) al_translate_transform(&camera_transform, 0, (.5*h - y)*0.01);

	if (x < 0 || x > w || y < 0 || y > w) al_translate_transform(&camera_transform, (.5*w - x), (.5*h - y));

}

const ALLEGRO_TRANSFORM * Player::Get_Transform()
{
	return &camera_transform;
}


Player::~Player()
{
	al_destroy_bitmap(image);
}
