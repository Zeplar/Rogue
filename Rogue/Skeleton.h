#pragma once
#include "Creature.h"
class Skeleton :
	public Creature
{
public:
	Skeleton();
	~Skeleton();

private:
	void Behavior();

	void Attack();
};

