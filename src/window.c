#include "window.h"
#include "sds.h"

 
/* this function creates an sdl window and sdl renderer, */
/* packaged into a single struct */
/* note: must initialize SDL before creating a window_struct. */
window *window_alloc(int w, int h)
{
	/* another way to initialize pointers to NULL: */
	/* *new = (struct window_struct){0}; */
	window *new = calloc(1, sizeof(window));
	if (!new)
		goto exit;
	new->sdl_window = SDL_CreateWindow("SDL Tutorial",
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED, w, h,
				SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!new->sdl_window)
		goto free;
	new->sdl_renderer = SDL_CreateRenderer(new->sdl_window, -1,
					   SDL_RENDERER_ACCELERATED |
					   SDL_RENDERER_PRESENTVSYNC);
	if (!new->sdl_renderer)
		goto free;
	new->width = w;
	new->height = h;
	new->mouse_focus = 1;
	new->keyboard_focus = 1;
	new->fullscreen = 0;
	new->minimized = 0;
exit:
	return new;
free:
	SDL_DestroyWindow(new->sdl_window);
	free(new);
	return NULL;
}

/* free a window */
void window_free(window *w)
{
	if (!w)
		return;
	SDL_DestroyRenderer(w->sdl_renderer);
	SDL_DestroyWindow(w->sdl_window);
	free(w);
}

/* handle a window event */
void window_handle_event(window *w, SDL_Event *e)
{
	int update_caption = 0;
	if (e->type == SDL_WINDOWEVENT) {
		switch (e->window.event) {
		/* change window size */
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			w->width = e->window.data1;
			w->height = e->window.data2;
			SDL_RenderPresent(w->sdl_renderer);
			break;
		/* render again on exposure */
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent(w->sdl_renderer);
			break;
		/* mouse entered window */
		case SDL_WINDOWEVENT_ENTER:
			w->mouse_focus = 1;
			update_caption = 1;
			break;
		/* mouse left window */
		case SDL_WINDOWEVENT_LEAVE:
			w->mouse_focus = 0;
			update_caption = 1;
			break;
		/* window has keyboard focus */
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			w->keyboard_focus = 1;
			update_caption = 1;
			break;
		/* window has lost keyboard focus */
		case SDL_WINDOWEVENT_FOCUS_LOST:
			w->keyboard_focus = 0;
			update_caption = 1;
			break;
		/* window minimized */
		case SDL_WINDOWEVENT_MINIMIZED:
			w->minimized = 1;
			break;
		/* window maximized */
		case SDL_WINDOWEVENT_MAXIMIZED:
			w->minimized = 0;
			break;
		/* window restored */
		case SDL_WINDOWEVENT_RESTORED:
			w->minimized = 0;
			break;
		}
		if (update_caption) {
			sds caption = sdsnew("SDL Tutorial - MouseFocus:");
			caption = sdscatprintf(caption,
				"MouseFocus:%s KeyBoardFocus:%s", 
				w->mouse_focus ? "On" : "Off",
				w->keyboard_focus ? "On" : "Off");
			SDL_SetWindowTitle(w->sdl_window, caption);
			sdsfree(caption);
		}
	} else if (e->type == SDL_KEYDOWN &&
		   e->key.keysym.sym == SDLK_RETURN){
		if (w->fullscreen) {
			SDL_SetWindowFullscreen(w->sdl_window, SDL_FALSE);
			w->fullscreen = 0;
		} else {
			SDL_SetWindowFullscreen(w->sdl_window, SDL_TRUE);
			w->fullscreen = 1;
			w->minimized = 0;
		}
	}
}

