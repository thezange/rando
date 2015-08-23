#include "stick.h"
#include "globals.h"
#define TICK_DELTA 10

stick *stick_alloc(int x, int y)
{
	stick *new = calloc(1, sizeof(stick));
	if (!new)
		goto exit;
	new->dim.x = x;
	new->dim.y = y;
	new->dim.w = 20;
	new->dim.h = 100;
exit:
	return new;
}

void stick_free(stick *s)
{
	free(s);
}

void stick_update(stick *s)
{
	/* move in correct direction */
	if (s->up && !s->down)
		s->dim.y -= TICK_DELTA;
	else if (!s->up && s->down)
		s->dim.y += TICK_DELTA;
	/* correct off-screen movement */
	if (s->dim.y < 0)
		s->dim.y = 0;
	else if (s->dim.y > g_window->height - s->dim.h)
		s->dim.y = g_window->height - s->dim.h;
}

void stick_render(stick *s)
{
	SDL_SetRenderDrawColor(g_window->sdl_renderer, 
				0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(g_window->sdl_renderer, (SDL_Rect *)s);
}

