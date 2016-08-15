#pragma once
#include "Entity.h"
#include "Tile.h"
class World;
class Player;

class Creature : public Entity
{
public:

	Tile::Characteristic MovementType;	//While all characteristics are valid, you should probably choose a movement characteristic.
	int hp, mp;
	float speed;
	enum Characteristics {Hostile};
	enum Animations {N, NE, E, SE, S, SW, W, NW};
	virtual void Update();
	void Draw();
	virtual void takeDamage(int damage, Player& source);
protected:
	int moveTimer = 0;

	std::vector<bool> Creature_Characteristics;
	bool IsInRange(const Entity& entity, int range);

	friend class World;

	void Find_Target_Player(int range);
	void MoveTowardTarget();
	void Move(int dx, int dy);
	std::unique_ptr<std::vector<std::pair<int, int>>> FindPathTo(int x, int y, int radius_to_search);
	Entity *target;
	static ALLEGRO_SAMPLE *sound_attack;
	static ALLEGRO_SAMPLE *sound_move;


private:
	class A_Star;
	static ALLEGRO_BITMAP *dir_marker;
};

