#ifndef _GLOBALS_H
#define _GLOBALS_H
#include "window.h"
#include "stick.h"
#include "ball.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

typedef struct {
	int player_score;
	int opponent_score;
	int player_event;
	int opponent_event;
} score_state;

extern window *g_window;
extern int run;
extern stick *g_player;
extern stick *g_opponent;
extern ball *g_ball;
extern score_state *g_score;

#endif
