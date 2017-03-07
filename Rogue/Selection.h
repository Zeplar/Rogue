#pragma once
#include "Drawable.h"
class Selection : public GUI::Drawable
{
public:
	Selection(const Coord& topLeft, const Coord& topRight);
	Selection(std::vector<Coord>& tiles);
	//null selection
	Selection();
	~Selection();
	Selection(const Selection& other);
	bool overlaps(Selection& other);
	void Draw();

	operator bool() const
	{
		return ((topLeft.x | topLeft.y) | (bottomRight.x | bottomRight.y)) != 0;
	}

	bool operator==(const Selection& other);

	friend std::ostream& operator<<(std::ostream& os, const Selection& s);

	int area();
	
	Coord topLeft;
	Coord bottomRight;
};

