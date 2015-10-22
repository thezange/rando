#include <SDL2/SDL.h>
#include "window.h"
#include "gameloop.h"
#include "stick.h"
#include "ball.h"
#include "globals.h"

/* starts up SDL and creates window */
int init();
/* loads media */
int load_media();
/* frees media and shuts down SDL */
void cleanup();
/* defining globals */
window *g_window = NULL;
stick *g_player = NULL;
stick *g_opponent = NULL;
ball *g_ball = NULL;
score_state *g_score = NULL;

/* perform initialization and start up game loop */
int main(int argc, char *argv[])
{
	int rval;
	/* start up SDL and create window */
	if (init() < 0) {
		fprintf(stderr, "failed to initialize!\n");
		rval = -1;
		goto exit;
	}
	/* load media */
	if (load_media() < 0) {
		fprintf(stderr, "failed to load media!\n");
		rval = -1;
		goto exit;
	}
	/* start game loop */
	printf("starting loop\n");
	game_loop();
	rval = 0;
exit:
	/* free resources and close SDL */
	cleanup();
	return rval;
}

/* initialize subsystems and allocate memory to objects */
int init()
{
	int rval;
	/* initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "SDL could not initialize! SDL_Error: "
				"%s\n", SDL_GetError());
		rval = -1;
		goto error;
	}
	/* create window (renderer comes with it) */
	g_window = window_alloc(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!g_window) {
		fprintf(stderr, "window could not be created!");
		rval = -1;
		goto error;
	}
	/* create player stick */
	g_player = stick_alloc(20, SCREEN_HEIGHT / 2);
	if (!g_player) {
		fprintf(stderr, "player could not be created!");
		rval = -1;
		goto error;
	}
	/* create opponent stick */
	g_opponent = stick_alloc(SCREEN_WIDTH - 40, SCREEN_HEIGHT / 2);
	if (!g_opponent) {
		fprintf(stderr, "player could not be created!");
		rval = -1;
		goto error;
	}
	/* create ball */
	g_ball = ball_alloc(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	if (!g_ball) {
		fprintf(stderr, "ball could not be created!");
		rval = -1;
		goto error;
	}
	/* create score struct */
	g_score = calloc(1, sizeof(score_state));
	if (!g_score) {
		fprintf(stderr, "score could not be created!");
		rval = -1;
		goto error;
	}
	g_score->player_score = 0;
	g_score->opponent_score = 0;
	rval = 0;
	return rval;
error:
	return rval;
}

/* load any media needed by the game */
int load_media()
{
	int rval;
	rval = 0;
exit:
	return rval;
}

/* free all allocated resources */
void cleanup()
{
	/* free  sticks */
	stick_free(g_player);
	g_player = NULL;
	stick_free(g_opponent);
	g_opponent = NULL;
	ball_free(g_ball);
	g_ball = NULL;
	/* destroy window */
	window_free(g_window);
	g_window = NULL;
	/* quit SDL subsystems */
	SDL_Quit();
}

