#ifndef FRONTEND_H
#define FRONTEND_H

#include "../../brickgame/tetris/tetris.h"
#include "../../brickgame/tetris/tetris_backend.h"

typedef struct Windows_t {
  WINDOW *screen;
  WINDOW *preview;
  WINDOW *stats;
  WINDOW *controlls;
} Windows_t;

Windows_t init_windows();

void display_whole_interface(Windows_t game_windows,
                             MoreGameInfo_t *MoreGameInfo);

void display_field(Windows_t game_windows, MoreGameInfo_t *MoreGameInfo);
void display_start_screen(Windows_t game_windows);
void display_game_over(Windows_t game_windows);
void display_stats(Windows_t game_windows, MoreGameInfo_t *MoreGameInfo);
void display_controlls(Windows_t game_windows);
void display_preview(Windows_t game_windows, MoreGameInfo_t *MoreGameInfo);
void display_pause_screen(Windows_t game_windows);
void clear_screen(Windows_t game_windows);

void free_windows(Windows_t game_windows);

void display_tet(Windows_t game_windows, MoreGameInfo_t *MoreGameInfo);
#endif