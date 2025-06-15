#include "../../gui/cli/frontend.h"
#include "fsm.h"
#include "tetris.h"
#include "tetris_backend.h"

void start_ncurses();
void game_loop(Windows_t game_windows);

/**
 * Main function of the program.
 *
 * @return 0 indicating successful execution.
 */
int main(void) {
  start_ncurses();
  Windows_t game_windows = init_windows();
  game_loop(game_windows);
  endwin();
  return 0;
}

/** Initializes the ncurses library and sets up the terminal for
 * non-blocking and silent input.
 *
 * @return void
 */
void start_ncurses() {
  initscr();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  noecho();
  cbreak();
  curs_set(0);
}
/** Function that runs the game loop, updating game status and user
 * input, and displaying the game interface.
 *
 * @return void
 */
void game_loop(Windows_t game_windows) {
  MoreGameInfo_t *MoreGameInfo =
      (MoreGameInfo_t *)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);

  while (MoreGameInfo->Status != TERMINATE) {
    if (MoreGameInfo->Status == START) {
      if (MoreGameInfo->Input == Start) {
        MoreGameInfo->first_time = FALSE;
      }
    }

    usleep(10000);

    user_action(MoreGameInfo, getch());     // updates input or status
    userInput(MoreGameInfo->Input, false);  // just kida chills

    if (MoreGameInfo->Status != (PAUSE && GAMEOVER && TERMINATE) &&
        MoreGameInfo->first_time == FALSE) {
      MoreGameInfo->GameInfo = updateCurrentState(MoreGameInfo);
    }

    display_whole_interface(game_windows, MoreGameInfo);
  }
  free_windows(game_windows);
  free_more_game_info(MoreGameInfo);
}
