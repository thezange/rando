#ifndef _BALL_H
#define _BALL_H
#include <SDL2/SDL.h>

typedef struct {
	SDL_Rect dim;
	int y_direction;
	int x_direction;
} ball;

ball *ball_alloc(int x, int y);
void ball_free(ball *b);
void ball_update(ball *b);
void ball_render(ball *b);

#endif
