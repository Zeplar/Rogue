#include "stdafx.h"
#include "Player.h"
#include "World.h"
#include <algorithm>



const int player_width = 10;
const int player_height = 20;
const int TIME_TO_MOVE = 20;

std::vector<Player*> Player::players = std::vector<Player*>();
Player* Player::primaryPlayer = NULL;
ALLEGRO_SAMPLE *Player::sound_attack = 0;
ALLEGRO_SAMPLE *Player::sound_move = 0;

Player::Player()
{
	speed = 20;
	MovementType = Tile::Characteristic::Flyable;

	ALLEGRO_BITMAP *raw = al_load_bitmap("C:/Users/JHep/Documents/Visual Studio 2015/Projects/Rogue/Rogue/Rogue/Tome/Monsters/HumanFighter.PNG");
	image = al_create_bitmap(Tile::TILE_W, Tile::TILE_H);
	al_set_target_bitmap(image);
	float xs = (float)Tile::TILE_W / al_get_bitmap_width(raw);
	float ys = (float)Tile::TILE_H / al_get_bitmap_height(raw);
	al_draw_scaled_rotated_bitmap(raw, al_get_bitmap_width(raw) / 2, al_get_bitmap_height(raw) / 2, Tile::TILE_W / 2, Tile::TILE_H / 2, 1, 1, 0, 0);
	al_destroy_bitmap(raw);
	al_convert_mask_to_alpha(image, al_map_rgb(255,0,255));
	al_identity_transform(&camera_transform);

	

}

Player* Player::make_player(int x, int y)
{
	Player *p = new Player();
	p->x = x;
	p->y = y;
	p->hp = 100;
	players.push_back(p);
	World::GetChunksAroundEntity(*p);
	World::getTile(x, y).entity = std::unique_ptr<Player>(p);
	return p;
}

void Player::Punch()
{
	int dx, dy;
	getDirection(dx, dy);
	Tile& target_location = World::getTile(x+dx, y+dy);

	if (target_location.entity && target_location.entity->Entity_Characteristics[Is_Creature])
	{
		dynamic_cast<Creature&>(*target_location.entity.get()).hp--;
	}
}

void Player::Behavior() 
{
	if (moveTimer == speed) std::cout << "Player: (" << x << "," << y << ") " << hp << std::endl;
}

void Player::SetDirection(const std::vector<bool>& key)
{
	int dx = key[ALLEGRO_KEY_RIGHT] - key[ALLEGRO_KEY_LEFT];
	int dy = key[ALLEGRO_KEY_DOWN] - key[ALLEGRO_KEY_UP];
	Creature::SetDirection(dx, dy);
}

void Player::Move(const std::vector<bool>& key)
{
	int dx, dy;
	Transform_Camera();

	if (moveTimer >= speed)
	{
		moveTimer = 0;
		SetDirection(key);
		dx = key[ALLEGRO_KEY_RIGHT] - key[ALLEGRO_KEY_LEFT];
		dy = key[ALLEGRO_KEY_DOWN] - key[ALLEGRO_KEY_UP];

		Creature::Move(dx, dy);

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
