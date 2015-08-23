#ifndef _WINDOW_H
#define _WINDOW_H
#include <SDL2/SDL.h>

typedef struct {
	SDL_Window *sdl_window;
	SDL_Renderer *sdl_renderer;
	int width;
	int height;
	int mouse_focus;
	int keyboard_focus;
	int fullscreen;
	int minimized;
} window;

window *window_alloc();
void window_free(window *w);
void window_handle_event(window *w, SDL_Event *e);

#endif
