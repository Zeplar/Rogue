// Rogue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>
#include "World.h"
#include <random>
#include "Skeleton.h"
#include "Player.h"
#include "Camera.h"
#include "Rogue.h"

int main()
{
	const int SCREEN_W = 2 * Chunk::size * Tile::TILE_W;
	const int SCREEN_H = 2 * Chunk::size * Tile::TILE_H;
	const float FPS = 60;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;

	bool redraw = false;	//Indicates that it's time to draw everything

	//Initialize a bunch of Allegro stuff like the display, keyboard, and FPS timer
	//=========================================================================================================
	if (!al_init())
	{
		std::cerr << "failed to initialize allegro\n";
		return -1;
	}

	if (!al_install_keyboard()) {
		std::cerr << "failed to install keyboard\n";
		return -1;
	}

	if (!al_install_mouse()) {
		std::cerr << "failed to install mouse\n";
		return -1;
	}

	if (!al_install_audio()) {
		std::cerr << "Failed to installed audio\n";
		return -1;
	}
	if (!al_init_acodec_addon())
	{
		std::cerr << "Failed to load audio codecs\n";
		return -1;
	}

	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 4, ALLEGRO_SUGGEST);


	//initialize display (w, h)
	display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display) {
		fprintf(stderr, "failed to create display\n");
		return -1;
	}


	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		fprintf(stderr, "failed to create timer\n");
		return -1;
	}

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_start_timer(timer);

	//=================================================================================================================
	std::cout << "Initializing World\n";
	
	World::SetDisplay(al_get_backbuffer(display));
	World::Initialize();
	auto primary = Player::make_player(0, 0);
	int x, y;
	primary->GetPosition(x, y);
	Skeleton::makeSkeleton(x+5, y+9);
	//=================================================================================================================
	std::cout << "Starting main loop\n";
	//Main loop
	while (true)
	{
		ALLEGRO_EVENT event;

		al_wait_for_event(event_queue, &event);

		if (event.type == ALLEGRO_EVENT_TIMER)
		{
			//Do anything that's framelocked

			//Player logic
			World::Update();

			//Prep the screen for drawing
			redraw = true;
		}



		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			break;

		else if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			World::key[event.keyboard.keycode] = true;
		}

		else if (event.type == ALLEGRO_EVENT_KEY_UP)
		{
			World::key[event.keyboard.keycode] = false;
		}

		else if (event.type == ALLEGRO_EVENT_KEY_CHAR)
		{
			World::keyPress = event.keyboard.unichar;
			World::timePressed = 0;
		}

		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			World::mouseDown = std::tuple<bool, int, int>(true, event.mouse.x, event.mouse.y);
		}

		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			World::mouseEvent = std::tuple<bool, int, int>(true, event.mouse.x, event.mouse.y);
			std::get<0>(World::mouseDown) = false;
		}

		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			al_set_target_bitmap(al_get_backbuffer(display));
			al_clear_to_color(al_map_rgb(0, 0, 0));

			World::Push_Matrix(primary->Get_Transform());
			primary->GetPosition(x, y);
			World::Draw(x,y);
			World::Pop_Matrix();
			Camera::drawScreen();
			al_flip_display();
		}
	}

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;

}

