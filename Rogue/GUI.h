#pragma once
#include "Entity.h"
#include "Drawable.h"

namespace GUI
{

	class Avatar : public Drawable
	{
	public:
		Avatar(ALLEGRO_BITMAP *image);
		~Avatar();
		void Draw();
	private:
		ALLEGRO_BITMAP *image;
	};

	class StatusBar : public Drawable
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

	class DirectionArrow : public Drawable
	{
	public:
		DirectionArrow(const Entity::Direction& direction);
		~DirectionArrow();
		void Draw();
	private:
		const Entity::Direction& direction;
	};
};

