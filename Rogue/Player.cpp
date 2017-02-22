#include "stdafx.h"
#include "Player.h"
#include "World.h"
#include "GUI.h"
#include <algorithm>
#include "TerrainMenu.h"



const int player_width = 10;
const int player_height = 20;
const int TIME_TO_MOVE = 20;


Player::Player() : Creature("Player")
{
	speed = 20;
	movementType = Tile::Characteristic::Flyable;

	ALLEGRO_BITMAP *raw = al_load_bitmap("C:/Users/Joshua/Documents/Visual Studio 2015/Projects/Rogue/Rogue/Rogue/Tome/Monsters/HumanFighter.PNG");
	image = al_create_bitmap(Tile::TILE_W, Tile::TILE_H);
	al_set_target_bitmap(image);
	float xs = (float)Tile::TILE_W / al_get_bitmap_width(raw);
	float ys = (float)Tile::TILE_H / al_get_bitmap_height(raw);
	al_draw_scaled_rotated_bitmap(raw, al_get_bitmap_width(raw) / 2, al_get_bitmap_height(raw) / 2, Tile::TILE_W / 2, Tile::TILE_H / 2, 1, 1, 0, 0);
	al_destroy_bitmap(raw);
	al_convert_mask_to_alpha(image, al_map_rgb(255,0,255));
	al_identity_transform(&camera.camera_transform);

	//Register the GUI components
	drawable_components.push_back(new GUI::Avatar(image));
	drawable_components.push_back(new GUI::DirectionArrow(direction));
}

Player* Player::make_player(int x, int y)
{
	Player *p = new Player();
	p->x = x;
	p->y = y;
	p->hp = 100;
	World::RegisterPlayer(p);
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
	SetDirection(World::key);
	Move(World::key);
}

void Player::SetDirection(const std::vector<bool>& key)
{
	int dx = key[ALLEGRO_KEY_RIGHT] - key[ALLEGRO_KEY_LEFT];
	int dy = key[ALLEGRO_KEY_DOWN] - key[ALLEGRO_KEY_UP];
	Creature::SetDirection(dx, dy);
}

void Player::Move(const std::vector<bool>& key)
{
	int dx = key[ALLEGRO_KEY_RIGHT] - key[ALLEGRO_KEY_LEFT];
	int dy = key[ALLEGRO_KEY_DOWN] - key[ALLEGRO_KEY_UP];

	if (moveTimer >= speed)
	{
		moveTimer = 0;
		Creature::Move(dx, dy);
	}

}

void Player::Draw()
{
	Creature::Draw();
	camera.Transform_Camera(x, y);
}


const ALLEGRO_TRANSFORM* Player::Get_Transform() const
{
	return &camera.camera_transform;
}


Player::~Player()
{
	al_destroy_bitmap(image);
	World::UnregisterPlayer(this);
}
