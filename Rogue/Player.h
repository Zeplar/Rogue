#pragma once
#include "stdafx.h"
#include "Entity.h"
#include "Creature.h"
#include "Item.h"
class World;

class Player : public Creature
{
public:
	Player();
	~Player();

	void Move(const std::vector<bool>& key);
	const ALLEGRO_TRANSFORM& Get_Transform();
	void Behavior();
	static Player* primaryPlayer;

private:
	static std::vector<Player*> players;
	void Punch();
	ALLEGRO_TRANSFORM camera_transform;
	void Transform_Camera();
	void SetDirection(const std::vector<bool>& key);
	std::vector<Item> Items;
	Item *Weapon;

	friend class World;
};

