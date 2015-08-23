#ifndef _STICK_H
#define _STICK_H
#include <SDL2/SDL.h>

typedef struct {
	SDL_Rect dim;
	int up;
	int down;
} stick;

stick *stick_alloc(int x, int y);
void stick_free(stick *s);
void stick_update(stick *s);
void stick_render(stick *s);

#endif
