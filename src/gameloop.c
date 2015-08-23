#include <SDL2/SDL.h>
#include "globals.h"
#define MS_PER_TICK 16.0
int run = 1;

static void process_input();
static void update();
static void render();

void game_loop()
{
	printf("score: %d - %d\n", g_score->player_score,
				   g_score->opponent_score);
	double prev = (double)SDL_GetTicks();
	double lag = 0.0;
	while (run) {
		double cur = (double)SDL_GetTicks();
		double elaps = cur - prev;
		prev = cur;
		lag += elaps;

		/* process input */
		process_input();

		/* move game forward by n ticks */
		while (lag >= MS_PER_TICK) {
			update();
			lag -= MS_PER_TICK;
		}

		/* render */
		render();
	}
}

static void process_input()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		/* user requests quit */
		if (e.type == SDL_QUIT) {
			run = 0;
		} else if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
				case SDLK_UP:
					g_player->up = 1;
					break;
				case SDLK_DOWN:
					g_player->down = 1;
					break;
				default:
					break;
			}
		} else if (e.type == SDL_KEYUP) {
			switch (e.key.keysym.sym) {
				case SDLK_UP:
					g_player->up = 0;
					break;
				case SDLK_DOWN:
					g_player->down = 0;
					break;
				default:
					break;
			}
		}
		/* handle window events */
		window_handle_event(g_window, &e);
	}
}

static void update()
{
	/* updating opponent AI first */
	if (g_ball->dim.y + 20 < g_opponent->dim.y) {
		g_opponent->up = 1;
		g_opponent->down = 0;
	} else if (g_ball->dim.y > g_opponent->dim.y + g_opponent->dim.h) {
		g_opponent->up = 0;
		g_opponent->down = 1;
	}
	/* updating game state */
	stick_update(g_player);
	stick_update(g_opponent);
	ball_update(g_ball);
	/* process score changes */
	if (g_score->player_event) {
		g_score->player_score++;
		if (g_score->player_score == 10) {
			printf("score: %d - %d\n", g_score->player_score,
						   g_score->opponent_score);
			printf("player wins!\n");
			run = 0;
		}
		g_ball->dim.x = SCREEN_WIDTH / 2;
		g_ball->dim.y = SCREEN_HEIGHT / 2;
		g_ball->x_direction = 1;
		g_ball->y_direction = -1;
		g_score->player_event = 0;
	} else if (g_score->opponent_event) {
		g_score->opponent_score++;
		if (g_score->opponent_score == 10) {
			printf("score: %d - %d\n", g_score->player_score,
						   g_score->opponent_score);
			printf("opponent wins!\n");
			run = 0;
		}
		g_ball->dim.x = SCREEN_WIDTH / 2;
		g_ball->dim.y = SCREEN_HEIGHT / 2;
		g_ball->x_direction = -1;
		g_ball->y_direction = 1;
		g_score->opponent_event = 0;
	}
}

static void render()
{
	SDL_SetRenderDrawColor(g_window->sdl_renderer, 
				0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(g_window->sdl_renderer);
	stick_render(g_player);
	stick_render(g_opponent);
	ball_render(g_ball);
	SDL_RenderPresent(g_window->sdl_renderer);
}

