#include "ball.h"
#include "globals.h"
#define BALL_VEL 4


ball *ball_alloc(int x, int y)
{
	ball *new = calloc(1, sizeof(ball));
	if (!new)
		goto exit;
	new->dim.x = x;
	new->dim.y = y;
	new->dim.w = 20;
	new->dim.h = 20;
	new->y_direction = 1;
	new->x_direction = -1;
exit:
	return new;
}

void ball_free(ball *b)
{
	free(b);
}

/* collision resolution simply repositions ball to site of
 * collision, and changes the direction of the motion. this is a
 * very simple simulation so we don't know the time of collision
 */
void ball_update(ball *b)
{
	b->dim.x += b->x_direction * BALL_VEL;
	b->dim.y += b->y_direction * BALL_VEL;
	/* check for x collisions */
	if (b->dim.x < 0) {
		g_score->opponent_event = 1;
	} else if (b->dim.x + b->dim.w > g_window->width) {
		g_score->player_event = 1;
	}
	/* check for y collisions */
	if (b->dim.y < 0) {
		b->dim.y = 0;
		b->y_direction = -b->y_direction;
	} else if (b->dim.y + b->dim.h > g_window->height) {
		b->dim.y = g_window->height - b->dim.h;
		b->y_direction = -b->y_direction;
	}
	/* check for collision with player stick */
	if (SDL_HasIntersection((SDL_Rect *)b, (SDL_Rect *)g_player)) {
		b->x_direction = 1;
		/* check to see if it was a vertical hit */
		if (b->dim.y > g_player->dim.y - 20 &&
		    b->dim.y < g_player->dim.y) {
			b->dim.y = g_player->dim.y - 20;
			b->y_direction = -1;
		} else if (g_player->dim.y + 100 - 20 < b->dim.y &&
			   g_player->dim.y + 100 > b->dim.y) {
			b->dim.y = g_player->dim.y + 100;
			b->y_direction = 1;
		}
	}
	/* check for collision with opponent stick */
	if (SDL_HasIntersection((SDL_Rect *)b, (SDL_Rect *)g_opponent)) {
		b->x_direction = -1;
		/* check to see if it was a vertical hit */
		if (b->dim.y > g_opponent->dim.y - 20 &&
		    b->dim.y < g_opponent->dim.y) {
			b->dim.y = g_opponent->dim.y - 20;
			b->y_direction = -1;
		} else if (g_opponent->dim.y + 100 - 20 < b->dim.y &&
			   g_opponent->dim.y + 100 > b->dim.y) {
			b->dim.y = g_opponent->dim.y + 100;
			b->y_direction = 1;
		}
	}
}

void ball_render(ball *b)
{
	SDL_SetRenderDrawColor(g_window->sdl_renderer, 
				0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(g_window->sdl_renderer, (SDL_Rect *)b);
}

