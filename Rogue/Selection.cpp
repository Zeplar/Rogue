#include "stdafx.h"
#include "Selection.h"
#include "Camera.h"

Selection::Selection(const Coord& topLeft, const Coord& bottomRight) : topLeft(topLeft), bottomRight(bottomRight)
{
	if (!topLeft.tile || !bottomRight.tile) std::cout << "Bad selection, coordinates are screen\n";
}

Selection::Selection(std::vector<Coord>& tiles)
{
	int x1, y1, x2, y2;
	x1 = y1 = LONG_MAX;
	x2 = y2 = 0;
	for (auto& t : tiles)
	{
		if (t.x < x1) x1 = t.x;
		if (t.y < y1) y1 = t.y;
		if (t.x > x2) x2 = t.x;
		if (t.y > y2) y2 = t.y;
	}

	topLeft = Coord(x1, y1, true);
	bottomRight = Coord(x2, y2, true);
}

Selection::Selection() : topLeft(Coord(0, 0,true)), bottomRight(Coord(0, 0,true))
{

}

Selection::Selection(const Selection& other) : topLeft(other.topLeft), bottomRight(other.bottomRight)
{

}

Selection::~Selection()
{
}

void Selection::Draw()
{
	Coord t = Camera::tileToScreen(topLeft);
	Coord b = Camera::tileToScreen(bottomRight + Coord(1,1,false));

	al_draw_rectangle(t.x, t.y, b.x, b.y, al_color_name("red"), 3);

}

Selection Selection::getScreen()
{
	Coord topLeft = Camera::screenToTile(Coord(0, 0, false));
	Coord bottomRight = Camera::screenToTile(Coord(al_get_display_width(al_get_current_display()), al_get_display_height(al_get_current_display()), false));
	return Selection(topLeft, bottomRight);
}

bool Selection::overlaps(Selection& other)
{
	if (!this || !other) return false;
	//rectangles are side by side
	if (other.topLeft.x > bottomRight.x || topLeft.x > other.bottomRight.x)
		return false;

	//rectangles are above-below
	if (other.topLeft.y > bottomRight.y || topLeft.y > other.bottomRight.y)
		return false;

	return true;
}

std::ostream& operator<<(std::ostream& os, const Selection& s)
{
	os << "(" << s.topLeft << "x" << s.bottomRight << ")";
	return os;
}

bool Selection::operator==(const Selection & other)
{
	return topLeft == other.topLeft && bottomRight == other.bottomRight;
}

int Selection::area()
{
	return (bottomRight.x - topLeft.x) * (bottomRight.y - topLeft.y);
}
