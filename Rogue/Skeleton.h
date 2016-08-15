#pragma once
#include "Creature.h"
class Skeleton :
	public Creature
{
public:
	static void makeSkeleton(int x, int y);
	~Skeleton();
	Skeleton();


private:
	void Behavior();
	void Attack();
};

