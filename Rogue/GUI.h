#pragma once
#include "Entity.h"

class GUI
{
public:
	GUI();
	~GUI();

	virtual void Draw() = 0;

	class StatusBar
	{
	public:
		StatusBar(const int& x, const int& y, const int& var, const int&max_value, ALLEGRO_COLOR color);
		~StatusBar();
		void Draw();
	private:
		const int& x;
		const int& y;
		const int& var;
		const int& max;
		ALLEGRO_COLOR color;
	};

	class DirectionArrow
	{
	public:
		DirectionArrow(const Entity::Direction& direction);
		~DirectionArrow();
		void Draw();
	private:
		const Entity::Direction& direction;
	};
};

