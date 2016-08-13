#include "stdafx.h"
#include "Skeleton.h"
#include "Player.h"
#include "World.h"

Skeleton::Skeleton()
{
}


Skeleton::~Skeleton()
{
}

void Skeleton::Behavior()
{
	if (moveTimer < speed) return;
	moveTimer = 0;

	Find_Target_Player(10);
	if (target)
	{
		MoveTowardTarget();
		Attack();
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
		dynamic_cast<Creature*>(target.entity.get())->hp--;
	}
}

