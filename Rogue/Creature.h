#pragma once
#include "Entity.h"
class World;

class Creature : public Entity
{
public:

	int MovementType;
	int hp, mp;
	float speed;
	enum Characteristics {Hostile};
protected:
	float moveTimer = 0;

	std::vector<bool> Creature_Characteristics;

	friend class World;

};

