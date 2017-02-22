#include "stdafx.h"
#include "Camera.h"
#include "World.h"
#include "TerrainMenu.h"
#include "TileMenu.h"
#include "Tile.h"

std::vector<GUI::Drawable*> Camera::screen;
ALLEGRO_TRANSFORM *Camera::current_transform = nullptr;

Camera::Camera()
{
	screen = std::vector<GUI::Drawable*>();
	screen.push_back(new TerrainMenu());
	screen.push_back(new TileMenu());
}


Camera::~Camera()
{
}

coord Camera::coordToScreen(const coord& c)
{
	int wx, wy;
	al_get_window_position(al_get_current_display(), &wx, &wy);

	float dx = c.first;
	float dy = c.second;
	dx -= wx + 8;	//These magic numbers are subtracting window borders I think. Probably specific to the computer.
	dy -= wy + 38;

	return coord(dx, dy);
}

void Camera::mouseToScreen(int& x, int& y)
{
	coord c;
	al_get_mouse_cursor_position(&c.first, &c.second);
	coord ret = coordToScreen(c);
	x = ret.first;
	y = ret.second;
}

coord Camera::mouseoverTile(coord& c)
{
	//These offsets set the top left walkable tile to 0,0. Otherwise some tiles are negative, which screws up the rounding on the integer division.
	const float x_offset = 16 * Tile::TILE_W;
	const float y_offset = 2 * Tile::TILE_H;

	coord scr = coordToScreen(c);
	float fx = scr.first; float fy = scr.second;
	ALLEGRO_TRANSFORM inverse;
	al_copy_transform(&inverse, current_transform);
	al_invert_transform(&inverse);
	al_transform_coordinates(&inverse, &fx, &fy);
	fx += x_offset;
	fy += y_offset;
	coord ret(fx / Tile::TILE_W, fy / Tile::TILE_H);
	
	return ret;
}

coord Camera::mouseoverTile()
{
	int x, y;
	mouseToScreen(x, y);
	return mouseoverTile(coord(x, y));
}

void Camera::selectionRectangle(coord& topLeft, coord& bottomRight)
{
	coord down(std::get<1>(World::mouseDown), std::get<2>(World::mouseDown));
	coord up;
	mouseToScreen(up.first, up.second);
	topLeft.first = std::min(down.first, up.first);
	topLeft.second = std::min(down.second, up.second);
	bottomRight.first = std::max(down.first, up.first);
	bottomRight.second = std::max(down.second, up.second);
}

std::vector<coord> Camera::mouseoverTiles()
{
	coord a, b;
	selectionRectangle(a, b);
	coord first = mouseoverTile(a);
	coord second = mouseoverTile(b);
	std::vector<coord> tiles;
	for (int i = first.second; i <= second.second; i++)
	{
		for (int j = first.first; j <= second.first; j++)
			if (!World::TileOutOfBounds(j,i))
				tiles.push_back(coord(j,i));
	}
	std::cout << "selected : " << tiles.size() << "\n";

	return tiles;
}

void Camera::Transform_Camera(float x, float y)
{
	float w = al_get_display_width(al_get_current_display());		//Screen width
	float h = al_get_display_height(al_get_current_display());		//Screen height


	al_transform_coordinates(al_get_current_transform(), &x, &y);
	if (x < .33*w || x > .66*w) al_translate_transform(&camera_transform, (.5*w - x) * 0.01, 0);
	if (y < .33*h || y > .66*h) al_translate_transform(&camera_transform, 0, (.5*h - y)*0.01);

	if (x < 0 || x > w || y < 0 || y > w) al_translate_transform(&camera_transform, (.5*w - x), (.5*h - y));

	current_transform = &camera_transform;

}

void Camera::drawScreen()
{
	if (std::get<0>(World::mouseDown))
		drawSelection();

	for each (auto i in screen) {
		i->Draw();
	}

	if (std::get<0>(World::mouseEvent))
	{
		selectTiles();
	}
	checkKeys();

}

void Camera::checkKeys()
{
	if (World::key[ALLEGRO_KEY_SPACE])
	{
		for (auto &p : Tile::currentlySelected) World::getTile(p).selected = false;
		Tile::currentlySelected.clear();
	}
}

void Camera::drawSelection()
{
	coord topLeft, bottomRight;
	Camera::selectionRectangle(topLeft, bottomRight);
	al_draw_rectangle(topLeft.first, topLeft.second, bottomRight.first, bottomRight.second, al_map_rgb(255, 0, 0), 1);
}

void Camera::selectTiles()
{
	auto selection = Camera::mouseoverTiles();

	//Save the currently selected tiles if shift is pressed
	if (World::key[ALLEGRO_KEY_LSHIFT])
	{
		for (auto &already_selected : Tile::currentlySelected)
			selection.push_back(already_selected);
	}

	//Clear the currently selected tiles. This prevents tiles from being added twice.
	for (auto &tile : Tile::currentlySelected)
	{
		World::getTile(tile).selected = false;
	}
	Tile::currentlySelected.clear();

	//Select the selection
	for (auto &p : selection)
		Tile::select(p);

	std::get<0>(World::mouseEvent) = false;
}