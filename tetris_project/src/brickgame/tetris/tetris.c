#include "tetris.h"

#include "fsm.h"
#include "tetris_backend.h"

/**
 * Updates the current state of the game based on the provided user input.
 *
 * @param user_input The action performed by the user.
 * @param hold Whether the user is holding the input or not.
 *
 * @return void
 *
 */
void userInput(UserAction_t user_input, bool hold) {
  (void)hold;
  MoreGameInfo_t *MoreGameInfo = get_current_game_more_game_info();
  MoreGameInfo->Input = user_input;
}

/**
 * Updates the current state of the game based on the provided user input.
 * Updates high score if necessary.
 *
 * @param MoreGameInfo A pointer to the MoreGameInfo_t struct that contains the
 * game information.
 *
 * @return A pointer to the updated GameInfo_t struct.
 *
 */
GameInfo_t *updateCurrentState(MoreGameInfo_t *MoreGameInfo) {
  iteration_runner(MoreGameInfo);
  if (MoreGameInfo->GameInfo->score > MoreGameInfo->GameInfo->high_score) {
    MoreGameInfo->GameInfo->high_score = MoreGameInfo->GameInfo->score;
    write_high_score(MoreGameInfo->GameInfo->score);
  }
  return MoreGameInfo->GameInfo;
}