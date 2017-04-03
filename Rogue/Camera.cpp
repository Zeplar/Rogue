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

Coord Camera::tileToScreen(const Coord& tile)
{
	if (!tile.tile) throw new Coord::CoordExcept();
	float xz = 0;
	float yz = 0;
	al_transform_coordinates(current_transform, &xz, &yz);
	int x = xz + (tile.x)*Tile::TILE_W;
	int y = yz + (tile.y)*Tile::TILE_H;
	return Coord(x, y, false);
}

Coord Camera::coordToScreen(const Coord& c)
{
	int wx = 0;
	int wy = 0;
	al_get_window_position(al_get_current_display(), &wx, &wy);

	float dx = c.x;
	float dy = c.y;
	dx -= wx +8;	//These magic numbers are subtracting window borders I think. Probably specific to the computer.
	dy -= wy +38;

	return Coord(dx, dy,false);
}

Coord Camera::mouseToScreen()
{
	Coord c(0,0,false);
	al_get_mouse_cursor_position(&c.x, &c.y);
	return coordToScreen(c);
}

Coord Camera::screenToTile(const Coord& c)
{
	if (c.tile) throw new Coord::CoordExcept();
	//These offsets set the top left walkable tile to 0,0. Otherwise some tiles are negative, which screws up the rounding on the integer division.
	const float x_offset = 16 * Tile::TILE_W;
	const float y_offset = 2 * Tile::TILE_H;

	Coord scr = coordToScreen(c);
	float fx = scr.x; float fy = scr.y;
	ALLEGRO_TRANSFORM inverse;
	al_copy_transform(&inverse, current_transform);
	al_invert_transform(&inverse);
	al_transform_coordinates(&inverse, &fx, &fy);
	fx += x_offset;
	fy += y_offset;
	return Coord(fx / Tile::TILE_W, fy / Tile::TILE_H, true);
}

Coord Camera::mouseoverTile()
{
	return screenToTile(mouseToScreen());
}

void Camera::selectionRectangle(Coord& topLeft, Coord& bottomRight)
{
	Coord down = World::mouseDown;
	Coord up = mouseToScreen();
	topLeft.x = std::min(down.x, up.x);
	topLeft.y = std::min(down.y, up.y);
	bottomRight.x = std::max(down.x, up.x);
	bottomRight.y = std::max(down.y, up.y);
}

std::vector<Coord> Camera::mouseoverTiles()
{
	Coord a, b;
	selectionRectangle(a, b);
	Coord first = screenToTile(a);
	Coord second = screenToTile(b);
	std::vector<Coord> tiles;
	for (int i = first.y; i <= second.y; i++)
	{
		for (int j = first.x; j <= second.x; j++)
			if (!World::TileOutOfBounds(j,i))
				tiles.push_back(Coord(j,i,true));
	}
	std::cout << "selected : " << tiles.size() << "\n";

	return tiles;
}

void Camera::Transform_Camera(float x, float y)
{
	float w = al_get_display_width(al_get_current_display());		//Screen width
	float h = al_get_display_height(al_get_current_display());		//Screen height
	const float speed = 0.005 * World::RenderDistance;

	al_transform_coordinates(al_get_current_transform(), &x, &y);
	if (x < .33*w || x > .66*w) al_translate_transform(&camera_transform, (.5*w - x) * speed, 0);
	if (y < .33*h || y > .66*h) al_translate_transform(&camera_transform, 0, (.5*h - y) * speed);

	if (x < 0 || x > w || y < 0 || y > w) al_translate_transform(&camera_transform, (.5*w - x), (.5*h - y));

	current_transform = &camera_transform;

}

void Camera::drawScreen()
{
	if (World::mouseDown.tile)
		drawSelection();

	for each (auto i in screen) {
		i->Draw();
	}

	if (World::mouseEvent.tile)
	{
		selectTiles();
	}
	checkKeys();

}

void Camera::checkKeys()
{
	if (World::key[ALLEGRO_KEY_ESCAPE])
	{
		for (auto &p : Tile::currentlySelected) World::getTile(p).selected = false;
		Tile::currentlySelected.clear();
	}
	if (World::key[ALLEGRO_KEY_PAD_PLUS])
	{
		World::RenderDistance += 1;
		World::key[ALLEGRO_KEY_PAD_PLUS] = false;
	}
	else if (World::key[ALLEGRO_KEY_PAD_MINUS])
	{
		World::RenderDistance -= 1;
		if (World::RenderDistance < 1) World::RenderDistance = 1;
		World::key[ALLEGRO_KEY_PAD_MINUS] = false;
	}
}

void Camera::drawSelection()
{
	Coord topLeft, bottomRight;
	Camera::selectionRectangle(topLeft, bottomRight);
	al_draw_rectangle(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y, al_map_rgb(255, 0, 0), 1);
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
		World::getChunk(tile).Redraw();
	}
	Tile::currentlySelected.clear();

	//Select the selection
	for (auto &p : selection) {
		Tile::select(p);
		World::getChunk(p).Redraw();
	}
	World::mouseEvent = Coord();
}