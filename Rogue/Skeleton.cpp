#include "stdafx.h"
#include "Skeleton.h"
#include "Player.h"
#include "World.h"

Skeleton::Skeleton()
{
	hp = 10;
	image = al_load_bitmap("C:/Users/JHep/Documents/Visual Studio 2015/Projects/Rogue/Rogue/Rogue/Tome/Monsters/Skeleton.PNG");
	al_convert_mask_to_alpha(image, al_map_rgb(255, 0, 255));
	if (!image) std::cerr << "Failed to load Skeleton.PNG" << std::endl;
	speed = 40;
	MovementType = Tile::Characteristic::Walkable;


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
	int x, y;
	if (moveTimer < speed) return;

	moveTimer = 0;
	
	Find_Target_Player(10);
	if (target)
	{
		target->GetPosition(x, y);
		if (auto path = FindPathTo(x, y, 20))
		{
			int dx = path->back().first;
			int dy = path->back().second;
			Move(dx, dy);
			SetDirection(dx, dy);
			//MoveTowardTarget();
			Attack();
		}
	}
	else
	{
		Move(1 - rand() % 3, 1 - rand() % 3);
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

