#pragma once
#include <iterator>

//Stores 2D location data. Each layer of the tree represents a subdivision of a square chunk into four smaller square chunks. The endpoint is individual tiles.
template<class T>
class Quadtree : std::iterator<std::bidirectional_iterator_tag, T>
{
public:
	Quadtree();
	~Quadtree();
	bool AddChild(T child, int loc);

private:
	T self;
	T[4] children;

};

