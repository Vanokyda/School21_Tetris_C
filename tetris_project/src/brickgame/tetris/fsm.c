#include "fsm.h"

/**
 * Runs one iteration of the game.
 *
 * @param MoreGameInfo a pointer to the MoreGameInfo_t struct
 *
 * @return void
 *
 */
void iteration_runner(MoreGameInfo_t *MoreGameInfo) {
  if (MoreGameInfo->Status != GAMEOVER) {
    if (MoreGameInfo->Status == SPAWN) {
      spawn_new_tet(MoreGameInfo);
    }
    if (MoreGameInfo->Count >= 60 - MoreGameInfo->GameInfo->speed * 5) {
      MoreGameInfo->Count = 0;
      tet_move_down(MoreGameInfo);
      down_check(MoreGameInfo);

    } else {
      switch (MoreGameInfo->Input) {
        case Start:
          if (MoreGameInfo->Status != GAMEOVER) {
            MoreGameInfo->Input = Start;
            MoreGameInfo->Status = START;
          }
          break;
        case Left:
          tet_move_left(MoreGameInfo);
          sides_check(MoreGameInfo);
          break;
        case Right:
          tet_move_right(MoreGameInfo);
          sides_check(MoreGameInfo);
          break;
        case Down:
          tet_move_down(MoreGameInfo);
          down_check(MoreGameInfo);
          break;
        case Action:
          tet_rotate(MoreGameInfo);
          rotate_check(MoreGameInfo);
          break;
        case Terminate:
          break;
        case Pause:
          break;
        case Up:
          break;
        default:
          break;
      }
      MoreGameInfo->Input = Up;
      MoreGameInfo->Count++;
    }
  }
}

/**
 * Checks for collision and rotates the tetromino three times if there is a
 * collision. If the game is not over, the game status is set to GAMING.
 *
 * @param MoreGameInfo a pointer to the MoreGameInfo_t struct
 *
 * @return void
 *
 */
void rotate_check(MoreGameInfo_t *MoreGameInfo) {
  if (collision_check(MoreGameInfo)) {
    for (int i = 0; i < 3; i++) {
      tet_rotate(MoreGameInfo);
    }
  }
  if (MoreGameInfo->Status != GAMEOVER) {
    MoreGameInfo->Status = GAMING;
  }
}

/**
 * Checks if the tetromino in the MoreGameInfo_t struct is colliding with the
 * sides of the game board. If a collision is detected, the tetromino is moved
 * in the opposite direction of the user's input. If the game is not over, the
 * game status is set to GAMING.
 *
 * @param MoreGameInfo a pointer to the MoreGameInfo_t struct
 *
 * @return void
 *
 */
void sides_check(MoreGameInfo_t *MoreGameInfo) {
  if (collision_check(MoreGameInfo)) {
    if (MoreGameInfo->Input == Left) {
      tet_move_right(MoreGameInfo);
    } else {
      tet_move_left(MoreGameInfo);
    }
  }
  if (MoreGameInfo->Status != GAMEOVER) {
    MoreGameInfo->Status = GAMING;
  }
}

/**
 * Checks if the current tetromino is in a collision state. If it is, the
 * tetromino is moved up and the game field is updated. The number of deleted
 * lines is calculated and added to the score. The game speed is updated.
 * Finally, the game status is set to SPAWN. If it isn't, the game status is set
 * to GAMING.
 *
 * @param MoreGameInfo a pointer to the MoreGameInfo_t struct
 *
 * @return void
 *
 */
void down_check(MoreGameInfo_t *MoreGameInfo) {
  if (collision_check(MoreGameInfo)) {
    if (MoreGameInfo->Status != GAMEOVER) {
      tet_move_up(MoreGameInfo);
      make_tet_field(MoreGameInfo);
      int del_lines = del_line_check(MoreGameInfo);
      MoreGameInfo->GameInfo->score += rows_to_points(del_lines);
      update_speed(MoreGameInfo);

      MoreGameInfo->Status = SPAWN;
    }
  } else {
    MoreGameInfo->Status = GAMING;
  }
}

/**
 * Updates the user action in the MoreGameInfo based on the provided user input.
 *
 * @param MoreGameInfo pointer to the MoreGameInfo_t struct representing the
 * game state
 * @param user_input the input key or character from the user
 *
 * @return void
 *
 */
void user_action(MoreGameInfo_t *MoreGameInfo, int user_input) {
  switch (user_input) {
    case 's':
      MoreGameInfo->Input = Start;
      break;
    case 'p':
      if (MoreGameInfo->Status != GAMEOVER &&
          MoreGameInfo->first_time == FALSE) {
        if (MoreGameInfo->Status == PAUSE && MoreGameInfo->first_time == FALSE)
          MoreGameInfo->Status = START;
        else
          MoreGameInfo->Status = PAUSE;
      }
      break;
    case 'q':
      MoreGameInfo->Input = Terminate;
      MoreGameInfo->Status = TERMINATE;
      break;
    case KEY_LEFT:
      MoreGameInfo->Input = Left;
      break;
    case KEY_RIGHT:
      MoreGameInfo->Input = Right;
      break;
    case KEY_DOWN:
      MoreGameInfo->Input = Down;
      break;
    case 'e':
      MoreGameInfo->Input = Action;
      break;
    case KEY_UP:
      break;
    default:
      break;
  }
}