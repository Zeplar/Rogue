#include "stdafx.h"
#include "Skeleton.h"
#include "Player.h"
#include "World.h"

Skeleton::Skeleton() : Creature("Skeleton")
{
	hp = 10;
	auto raw = al_load_bitmap("C:/Users/JHep/Documents/Visual Studio 2015/Projects/Rogue/Rogue/Rogue/Tome/Monsters/Skeleton.PNG");
	al_convert_mask_to_alpha(raw, al_map_rgb(255, 0, 255));

	image = al_create_bitmap(Tile::TILE_W, Tile::TILE_H);
	al_set_target_bitmap(image);

	al_draw_bitmap(raw, -11, -13, 0);
	al_destroy_bitmap(raw);
	speed = 40;
	movementType = Tile::Characteristic::Walkable;


	if (!al_reserve_samples(10)) std::cerr << "Failed to reserve audio samples\n";
	sound_attack = al_load_sample("C:/Users/JHep/Documents/Visual Studio 2015/Projects/Rogue/Rogue/Rogue/Audio/sword_1.WAV");
	if (!sound_attack) std::cerr << "Failed to load audio file\n";
}

void Skeleton::makeSkeleton(int x, int y)
{
	Tile &spawn = World::getTile(x, y);
	if (spawn.entity)
	{
		std::cerr << "Spawn position blocked by entity" << std::endl;
		return;
	}
	spawn.entity = std::make_unique<Skeleton>();
	spawn.entity->SetPosition(x, y);
}

Skeleton::~Skeleton()
{
}


void Skeleton::Behavior()
{
	static coord tile_target;
	if (moveTimer < speed) return;

	moveTimer = 0;
	
	if (!target) target = Find_Target_Player(10);
	if (target && target->getTile().Characteristics()[movementType])
		target->GetPosition(tile_target.first, tile_target.second);

	if (auto path = FindPathTo(tile_target.first, tile_target.second, 10))
	{
		int dx = path->back().first;
		int dy = path->back().second;
		Move(dx, dy);
		SetDirection(dx, dy);
		Attack();
	}

	if (x == tile_target.first && y == tile_target.second)
	{
		tile_target.first += std::rand() % 10 - 5;
		tile_target.second += std::rand() % 10 - 5;
	}
}

void Skeleton::Attack()
{
	int dx, dy;
	getDirection(dx, dy);
	Tile& target = World::getTile(x + dx, y + dy);
	if (target.entity && dynamic_cast<Creature*>(target.entity.get()))
	{
		dynamic_cast<Creature*>(target.entity.get())->takeDamage(5, *this);
		al_play_sample(sound_attack, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	}
}

