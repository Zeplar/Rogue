#pragma once

class Tile;
class Entity
{

public:
	Entity(std::string name);
	~Entity();
	virtual void Draw();
	virtual void Behavior() = 0;
	virtual void Update() = 0;
	enum Characteristics {Immovable, Passable, Is_Item, Is_Creature};
	enum Direction { N, NE, E, SE, S, SW, W, NW };

	std::vector<bool> Entity_Characteristics;

	void SetPosition(int x, int y);
	void GetPosition(int& x, int& y) const;
	std::string name;

	static double getDirection(Direction EntityDirection);
	Tile& getTile();

protected:

	ALLEGRO_BITMAP *image;
	Direction direction; //direction enum
	int x, y;
	void getDirection(int &dx, int &dy);
	void SetDirection(int &dx, int &dy);


};

