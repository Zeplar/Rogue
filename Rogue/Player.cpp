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

	ALLEGRO_BITMAP *raw = al_load_bitmap("C:/Users/JHep/Documents/Visual Studio 2015/Projects/Rogue/Rogue/Rogue/creatures/Player.bmp");
	image = al_create_bitmap(Tile::TILE_W, Tile::TILE_H);
	al_set_target_bitmap(image);
	float xs = (float)Tile::TILE_W / al_get_bitmap_width(raw);
	float ys = (float)Tile::TILE_H / al_get_bitmap_height(raw);
	al_draw_scaled_rotated_bitmap(raw, al_get_bitmap_width(raw) / 2, al_get_bitmap_height(raw) / 2, Tile::TILE_W / 2, Tile::TILE_H / 2, xs, ys, M_PI, 0);
	al_destroy_bitmap(raw);
	al_convert_mask_to_alpha(image, al_map_rgb(255,0,255));
	al_identity_transform(&camera_transform);

	players.push_back(this);
}
//
//void Player::Punch()
//{
//	int dx, dy;
//	getDirection(dx, dy);
//	Tile* target_location = World::getTile(dx, dy);
//
//	if (target_location->)
//}

void Player::Behavior() {}

void Player::SetDirection(const std::vector<bool>& key)
{
	if (key[ALLEGRO_KEY_UP]) {
		if (key[ALLEGRO_KEY_LEFT]) direction = Entity::Direction::NW;
		else if (key[ALLEGRO_KEY_RIGHT]) direction = Entity::Direction::NE;
		else direction = Entity::Direction::N;
	}
	else if (key[ALLEGRO_KEY_DOWN]) {
		if (key[ALLEGRO_KEY_RIGHT]) direction = Direction::SE;
		else if (key[ALLEGRO_KEY_LEFT]) direction = Direction::SW;
		else direction = Direction::S;
	}
	else {
		if (key[ALLEGRO_KEY_LEFT]) direction = Direction::W;
		else if (key[ALLEGRO_KEY_RIGHT]) direction = Direction::E;
		else direction = Direction::N;
	}
}

void Player::Move(const std::vector<bool>& key)
{
	float tempX = x;
	float tempY = y;
	if (key[ALLEGRO_KEY_DOWN] || key[ALLEGRO_KEY_UP] || key[ALLEGRO_KEY_LEFT] || key[ALLEGRO_KEY_RIGHT])
		moveTimer++;

	if (moveTimer >= speed)
	{
		moveTimer = 0;
		SetDirection(key);
		tempX = key[ALLEGRO_KEY_RIGHT] - key[ALLEGRO_KEY_LEFT] + x;
		tempY = key[ALLEGRO_KEY_DOWN] - key[ALLEGRO_KEY_UP] + y;

		if (World::getTile(tempX, tempY).Characteristics()[MovementType])
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

const ALLEGRO_TRANSFORM& Player::Get_Transform()
{
	return camera_transform;
}


Player::~Player()
{
	al_destroy_bitmap(image);
}
