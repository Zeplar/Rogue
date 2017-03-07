#include "stdafx.h"
#include "Coord.h"

std::ostream & operator<<(std::ostream & os, const Coord & c)
{
	os << "(" << c.x << "," << c.y << ")";
	return os;
}
