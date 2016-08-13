#pragma once
class Entity
{
friend class World;

public:
	Entity();
	~Entity();
	void Draw();
	virtual void Behavior() = 0;
	virtual void Update() = 0;
	enum Characteristics {Immovable, Passable, Is_Item, Is_Creature};
	enum Direction { N, NE, E, SE, S, SW, W, NW };

	std::vector<bool> Entity_Characteristics;

	void SetPosition(int x, int y);
	void GetPosition(int& x, int& y) const;

protected:

	ALLEGRO_BITMAP *image;
	Direction direction; //direction enum
	int x, y;
	double getDirection(Direction EntityDirection);
	void getDirection(int &dx, int &dy);

};

