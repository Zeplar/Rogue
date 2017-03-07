#pragma once
#include <exception>
struct Coord
{
public:
	Coord(int x, int y, bool tile) : x(x), y(y), tile(tile) {}
	
//	Coord(Coord& other) : x(other.x), y(other.y), tile(other.tile) {}

	~Coord() {}

	Coord() : x(-1), y(-1), tile(false) {}

	int x;
	int y;
	bool tile;

	friend std::ostream& operator<<(std::ostream& os, const Coord& c);

	bool operator==(const Coord& other)
	{
		if (tile != other.tile) throw new CoordExcept();
		return x == other.x && y == other.y;
	}

	operator bool()
	{
		return !(x == -1 && y == -1);
	}

	Coord operator+(const Coord& rh)
	{
		return Coord(x + rh.x, y + rh.y, tile);
	}

	Coord operator-(const Coord& rh)
	{
		return Coord(x - rh.x, y - rh.y, tile);
	}

	Coord operator*(int rh)
	{
		return Coord(x*rh, y*rh, tile);
	}

	bool operator< (const Coord& other) const {
		if (x < other.x) return true;
		return (x == other.x) && y < other.y;
	}

	class CoordExcept : public std::exception
	{
		virtual const char* what() const throw()
		{
			return "Bad coordinate";
		}
	};

};

