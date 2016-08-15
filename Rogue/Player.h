#pragma once
#include "stdafx.h"
#include "Entity.h"
#include "Creature.h"
#include "Item.h"
class World;

class Player : public Creature
{
public:
	~Player();

	const ALLEGRO_TRANSFORM* Get_Transform() const;
	void Behavior();
	static Player *make_player(int x, int y);

private:
	void Punch();
	ALLEGRO_TRANSFORM camera_transform;
	void Transform_Camera();
	void SetDirection(const std::vector<bool>& key);
	std::vector<Item*> Items;
	Item *Weapon;
	Player();
	void Move(const std::vector<bool>& key);

};

