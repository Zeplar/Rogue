#pragma once
class Entity
{
friend class World;

public:
	Entity();
	~Entity();
	void Draw();
	virtual void Behavior() = 0;
	enum Characteristics {Immovable, Passable, Is_Item, Is_Creature};
	enum Direction { N, NE, E, SE, S, SW, W, NW };

protected:

	ALLEGRO_BITMAP *image;
	int direction; //direction enum
	int x, y;
	std::vector<bool> Entity_Characteristics;
	double getDirection(int Entity_Direction);

};

