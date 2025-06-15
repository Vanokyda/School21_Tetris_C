#include "frontend.h"

/**
 * Displays the whole interface based on the current game status and more game
 * info.
 *
 * @param game_windows The windows structure containing the game windows.
 * @param MoreGameInfo The more game info structure containing the game status
 * and other information.
 *
 * @return void
 */
void display_whole_interface(Windows_t game_windows,
                             MoreGameInfo_t *MoreGameInfo) {
  if (MoreGameInfo->Status == START && MoreGameInfo->first_time == TRUE) {
    display_start_screen(game_windows);
  } else if (MoreGameInfo->Status == PAUSE) {
    display_pause_screen(game_windows);
  } else if (MoreGameInfo->Status == GAMEOVER) {
    display_game_over(game_windows);
  } else {
    clear_screen(game_windows);  // мб не нужно? Нужно
    display_field(game_windows, MoreGameInfo);
    display_tet(game_windows, MoreGameInfo);
  }

  display_preview(game_windows, MoreGameInfo);
  display_stats(game_windows, MoreGameInfo);
  display_controlls(game_windows);

  wrefresh(game_windows.screen);
  wrefresh(game_windows.preview);
  wrefresh(game_windows.stats);
  wrefresh(game_windows.controlls);
}

/**
 * Initializes the game windows for the GUI.
 *
 * @return Windows_t A structure containing the initialized game windows.
 *
 * @note The function creates four windows: screen, preview, stats, and
 * controls. It sets the color pairs and background color for each window. It
 * also draws boxes around each window.
 */
Windows_t init_windows() {
  Windows_t game_windows;
  int y_screen_start = 0;
  int x_screen_start = 0;
  int y_screen_size = 22;
  int x_screen_size = 22;
  game_windows.screen =
      newwin(y_screen_size, x_screen_size, y_screen_start, x_screen_start);

  int y_preview_start = 0;
  int x_preview_start = x_screen_size + 2;
  int y_preview_size = y_screen_size / 3 - 3;
  int x_preview_size = x_screen_size / 2;
  game_windows.preview =
      newwin(y_preview_size, x_preview_size, y_preview_start, x_preview_start);

  int y_stats_start = y_preview_size + 0.5;
  int x_stats_start = x_screen_size + 2;
  int y_stats_size = y_screen_size / 3 + 2;
  int x_stats_size = x_screen_size / 1.5;
  game_windows.stats =
      newwin(y_stats_size, x_stats_size, y_stats_start, x_stats_start);

  int y_controlls_start = y_stats_start + y_stats_size + 0.5;
  int x_controlls_start = x_screen_size + 2;
  int y_controlls_size = y_screen_size / 3 + 2;
  int x_controlls_size = x_screen_size / 1.5;
  game_windows.controlls = newwin(y_controlls_size, x_controlls_size,
                                  y_controlls_start, x_controlls_start);

  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);

  init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(3, COLOR_RED, COLOR_BLACK);
  init_pair(4, COLOR_YELLOW, COLOR_BLACK);
  init_pair(5, COLOR_CYAN, COLOR_BLACK);

  init_pair(6, COLOR_BLUE, COLOR_BLACK);
  init_pair(7, COLOR_WHITE, COLOR_BLACK);

  wbkgdset(game_windows.screen, COLOR_PAIR(7));
  wbkgdset(game_windows.preview, COLOR_PAIR(7));
  wbkgdset(game_windows.stats, COLOR_PAIR(7));
  wbkgdset(game_windows.controlls, COLOR_PAIR(7));
  refresh();

  box(game_windows.screen, 0, 0);
  box(game_windows.preview, 0, 0);
  box(game_windows.stats, 0, 0);
  box(game_windows.controlls, 0, 0);

  return game_windows;
}

/**
 * Displays current tetromino on the game screen.
 *
 * @param game_windows The structure containing the game window handles.
 * @param MoreGameInfo A pointer to the structure containing additional game
 * information.
 *
 * @return void
 *
 */
void display_tet(Windows_t game_windows, MoreGameInfo_t *MoreGameInfo) {
  for (int row = 0; row < TET_SIZE; row++) {
    for (int col = 0; col < TET_SIZE; col++) {
      int ty = MoreGameInfo->tet_y + row;
      int tx = MoreGameInfo->tet_x + col;

      if (MoreGameInfo->tet[row][col] != 0) {
        wbkgdset(game_windows.screen, COLOR_PAIR(MoreGameInfo->colour));
        mvwprintw(game_windows.screen, ty + 1, 2 * tx + 1, "{");
        mvwprintw(game_windows.screen, ty + 1, 2 * tx + 2, "}");
      }
    }
  }
}

/**
 * Displays the game field on the game screen.
 *
 * @param game_windows The structure containing the game window handles.
 * @param MoreGameInfo A pointer to the structure containing additional game
 * information.
 *
 * @return void
 */
void display_field(Windows_t game_windows, MoreGameInfo_t *MoreGameInfo) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      if (MoreGameInfo->GameInfo->field[i][j] == 1) {
        wbkgdset(game_windows.screen, COLOR_PAIR(6));
        mvwprintw(game_windows.screen, i + 1, 2 * j + 1, "{");
        mvwprintw(game_windows.screen, i + 1, 2 * j + 2, "}");
      } else {
        mvwprintw(game_windows.screen, i + 1, 2 * j + 1, " ");
        mvwprintw(game_windows.screen, i + 1, 2 * j + 2, " ");
      }
    }
  }
}

/**
 * Clears the screen by erasing the contents and drawing a border around the
 * game screen.
 *
 * @param game_windows A structure containing the game window handles.
 *
 * @return void
 */
void clear_screen(Windows_t game_windows) {
  werase(game_windows.screen);
  wbkgdset(game_windows.screen, COLOR_PAIR(7));
  box(game_windows.screen, 0, 0);
}

/**
 * Displays a pause screen on the game screen.
 *
 * @param game_windows The structure containing the game window handles.
 *
 * @return void
 *
 */
void display_pause_screen(Windows_t game_windows) {
  wbkgdset(game_windows.screen, COLOR_PAIR(7));
  mvwprintw(game_windows.screen, 8, 1, "====================");
  mvwprintw(game_windows.screen, 9, 1, "        PAUSE       ");
  mvwprintw(game_windows.screen, 10, 1, "====================");
}

/**
 * Displays a "Game Over" message on the game screen.
 *
 * @param game_windows The structure containing the game window handles.
 *
 * @return void
 */
void display_game_over(Windows_t game_windows) {
  wbkgdset(game_windows.screen, COLOR_PAIR(7));
  mvwprintw(game_windows.screen, 8, 1, "======GAME OVER=====");
  mvwprintw(game_windows.screen, 9, 1, " PRESS \"q\" TO QUIT  ");
  mvwprintw(game_windows.screen, 10, 1, "====================");
}

/**
 * Displays the start screen for the S21_Tetris game on the game_screen.
 *
 * @param game_windows A structure containing the handles for the game window.
 *
 * @return void
 */
void display_start_screen(Windows_t game_windows) {
  wbkgdset(game_windows.screen, COLOR_PAIR(7));
  mvwprintw(game_windows.screen, 8, 1, "=====S21_TETRIS=====");
  mvwprintw(game_windows.screen, 9, 2, "PRESS \"s\" TO START");
  mvwprintw(game_windows.screen, 10, 2, "PRESS \"q\" TO QUIT");
  mvwprintw(game_windows.screen, 11, 1, "====================");
}

/**
 * Displays the game statistics on the game window.
 *
 * @param game_windows A structure containing the handles for the game window.
 * @param MoreGameInfo A pointer to the structure containing additional game
 * information.
 *
 * @return void
 *
 */
void display_stats(Windows_t game_windows, MoreGameInfo_t *MoreGameInfo) {
  mvwprintw(game_windows.stats, 0, 0, "Game Info:");
  mvwprintw(game_windows.stats, 2, 1, "Score: %d",
            MoreGameInfo->GameInfo->score);

  mvwprintw(game_windows.stats, 4, 1, "Top:   %d",
            MoreGameInfo->GameInfo->high_score);

  mvwprintw(game_windows.stats, 6, 1, "Speed: %d",
            MoreGameInfo->GameInfo->speed);
}

/**
 * Displays the game controls on the controlls screen.
 *
 * @param game_windows A structure containing the handles for the game window.
 *
 * @return void
 *
 */
void display_controlls(Windows_t game_windows) {
  mvwprintw(game_windows.controlls, 0, 0, "Controlls:");
  mvwprintw(game_windows.controlls, 2, 1, "Move:");
  mvwprintw(game_windows.controlls, 3, 2, "<- | ->");
  mvwprintw(game_windows.controlls, 4, 2, "   V");
  mvwprintw(game_windows.controlls, 5, 1, "Turn:   E");
  mvwprintw(game_windows.controlls, 6, 1, "Pause:  P");
  mvwprintw(game_windows.controlls, 7, 1, "Exit:   Q");
}

/**
 * Displays the preview of the next tetrimino in the preview screen.
 *
 * @param game_windows The structure containing the game windows.
 * @param MoreGameInfo A pointer to the MoreGameInfo_t struct containing game
 * information.
 *
 * @return void
 *
 */
void display_preview(Windows_t game_windows, MoreGameInfo_t *MoreGameInfo) {
  werase(game_windows.preview);
  box(game_windows.preview, 0, 0);
  mvwprintw(game_windows.preview, 0, 0, "Preview:");

  for (int i = 0; i < TET_SIZE; i++) {
    for (int j = 0; j < TET_SIZE; j++) {
      if (MoreGameInfo->GameInfo->next[i][j] == 1) {
        wbkgdset(game_windows.preview, COLOR_PAIR(MoreGameInfo->next_colour));
        mvwprintw(game_windows.preview, i + 1, 2 * j + 1, "{");
        mvwprintw(game_windows.preview, i + 1, 2 * j + 2, "}");
      }
    }
  }
  wbkgdset(game_windows.preview, COLOR_PAIR(7));
}

/**
 * Frees the memory allocated for the game windows.
 *
 * @param game_windows The structure containing the game windows.
 *
 * @return void
 *
 */
void free_windows(Windows_t game_windows) {
  delwin(game_windows.screen);
  delwin(game_windows.preview);
  delwin(game_windows.stats);
  delwin(game_windows.controlls);
}
