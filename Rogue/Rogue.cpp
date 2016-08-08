// Rogue.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <time.h>
#include "Player.h"
#include "Tile.h"
#include "Chunk.h"
#include <random>



int main()
{

	const int SCREEN_W = 2 * Chunk::size * Tile::TILE_W;
	const int SCREEN_H = 2 * Chunk::size * Tile::TILE_H;
	const float FPS = 60;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	Player *player = NULL;
	Chunk chunk;


	bool key[ALLEGRO_KEY_MAX]; //Array indicating which keys were pressed last time we checked
	for (int i = 0; i < ALLEGRO_KEY_MAX; i++) key[i] = false;
	bool redraw = false;	//Indicates that it's time to draw everything

	//Initialize a bunch of Allegro stuff like the display, keyboard, and FPS timer
	//=========================================================================================================
	if (!al_init())
	{
		fprintf(stderr, "failed to initialize allegro\n");
		return -1;
	}

	if (!al_install_keyboard()) {
		fprintf(stderr, "failed to install keyboard\n");
		return -1;
	}
	al_init_image_addon();
	al_init_primitives_addon();

	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 4, ALLEGRO_SUGGEST);


	for (int i = 0; i < chunk.size; i++)
		for (int j = 0; j < chunk.size; j++)
		{
			chunk.data[i][j] = (std::rand() % 2) ? Tile::Forest() : Tile::Forest_Floor();
		}

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

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);

	//=================================================================================================================

	player = new Player();
	

	al_set_target_bitmap(al_get_backbuffer(display));

	//=================================================================================================================

	//Main loop
	while (!key[ALLEGRO_KEY_ESCAPE])
	{
		ALLEGRO_EVENT event;

		al_wait_for_event(event_queue, &event);

		if (event.type == ALLEGRO_EVENT_TIMER)
		{
			//Do anything that's framelocked

			//Player logic
			player->Move(key);

			//Prep the screen for drawing
			redraw = true;
		}



		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			break;

		else if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			key[event.keyboard.keycode] = true;
		}

		else if (event.type == ALLEGRO_EVENT_KEY_UP)
		{
			key[event.keyboard.keycode] = false;
		}

		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));
			chunk.Draw();
			player->Draw();
			al_flip_display();
		}
	}

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;

}

