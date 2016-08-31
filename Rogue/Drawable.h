#pragma once
namespace GUI
{
	//Interface with the method Draw()
	//May add layers later
	class Drawable
	{
	public:
		virtual void Draw() = 0;
	};
}