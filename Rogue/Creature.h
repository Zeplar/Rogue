#pragma once
#include "Entity.h"
#include "Tile.h"
class World;
class Player;

class Creature : public Entity
{
public:

	Tile::Characteristic movementType;	//While all characteristics are valid, you should probably choose a movement characteristic.
	int hp, mp;
	float speed;
	enum Characteristics {Hostile};
	enum Animations {N, NE, E, SE, S, SW, W, NW};
	virtual void Update();

	//Takes damage and calls virtual Die() if hp <= 0
	virtual void takeDamage(int damage, Entity& source);
protected:
	int moveTimer = 0;

	std::vector<bool> Creature_Characteristics;
	bool IsInRange(const Entity& entity, int range);

	friend class World;

	Entity* Find_Target_Player(int range);
	void MoveTowardTarget();
	void Move(int dx, int dy);
	std::unique_ptr<std::vector<std::pair<int, int>>> FindPathTo(int x, int y, int radius_to_search);
	Entity *target;
	static ALLEGRO_SAMPLE *sound_attack;
	static ALLEGRO_SAMPLE *sound_move;

	//Releases the tile pointer to this creature
	virtual void Die();
	Creature(std::string name);

private:
	class A_Star;
	static ALLEGRO_BITMAP *dir_marker;
};

