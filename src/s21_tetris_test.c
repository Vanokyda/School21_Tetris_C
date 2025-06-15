#ifndef _S21_TETRIS_TEST_
#define _S21_TETRIS_TEST_

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "./brickgame/tetris/fsm.h"
#include "./brickgame/tetris/tetris.h"
#include "./brickgame/tetris/tetris_backend.h"

START_TEST(iteration_runner_test1) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  MoreGameInfo->Status = SPAWN;
  iteration_runner(MoreGameInfo);
  ck_assert_int_eq(MoreGameInfo->Status, GAMING);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(iteration_runner_test2) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  MoreGameInfo->Status = SPAWN;
  MoreGameInfo->Count = 60;
  iteration_runner(MoreGameInfo);
  ck_assert_int_eq(MoreGameInfo->Count, 0);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(iteration_runner_test3) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  MoreGameInfo->Status = SPAWN;
  MoreGameInfo->Input = Start;
  iteration_runner(MoreGameInfo);
  ck_assert_int_eq(MoreGameInfo->Input, Up);
  ck_assert_int_eq(MoreGameInfo->Status, START);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(iteration_runner_test4) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  MoreGameInfo->Status = SPAWN;
  MoreGameInfo->Input = Left;
  iteration_runner(MoreGameInfo);
  ck_assert_int_eq(MoreGameInfo->Input, Up);
  ck_assert_int_eq(MoreGameInfo->Status, GAMING);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(iteration_runner_test5) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  MoreGameInfo->Status = SPAWN;
  MoreGameInfo->Input = Right;
  iteration_runner(MoreGameInfo);
  ck_assert_int_eq(MoreGameInfo->Input, Up);
  ck_assert_int_eq(MoreGameInfo->Status, GAMING);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(iteration_runner_test6) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  MoreGameInfo->Status = SPAWN;
  MoreGameInfo->Input = Down;
  iteration_runner(MoreGameInfo);
  ck_assert_int_eq(MoreGameInfo->Input, Up);
  ck_assert_int_eq(MoreGameInfo->Status, GAMING);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(iteration_runner_test7) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  MoreGameInfo->Status = SPAWN;
  MoreGameInfo->Input = Action;
  iteration_runner(MoreGameInfo);
  ck_assert_int_eq(MoreGameInfo->Input, Up);
  ck_assert_int_eq(MoreGameInfo->Status, GAMING);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(iteration_runner_test8) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  MoreGameInfo->Status = SPAWN;
  MoreGameInfo->Input = Terminate;
  iteration_runner(MoreGameInfo);
  ck_assert_int_eq(MoreGameInfo->Input, Up);
  ck_assert_int_eq(MoreGameInfo->Status, GAMING);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(iteration_runner_test9) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  MoreGameInfo->Status = SPAWN;
  MoreGameInfo->Input = Pause;
  iteration_runner(MoreGameInfo);
  ck_assert_int_eq(MoreGameInfo->Input, Up);
  ck_assert_int_eq(MoreGameInfo->Status, GAMING);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(iteration_runner_test10) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  MoreGameInfo->Status = SPAWN;
  MoreGameInfo->Input = 20;
  iteration_runner(MoreGameInfo);
  ck_assert_int_eq(MoreGameInfo->Input, Up);
  ck_assert_int_eq(MoreGameInfo->Status, GAMING);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(rotation_check_test1) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  MoreGameInfo->Status = GAMING;
  MoreGameInfo->Input = Action;
  for (int i = 0; i < TET_SIZE; i++) {
    for (int j = 0; j < TET_SIZE; j++) {
      MoreGameInfo->tet[i][j] = 0;
    }
  }
  for (int i = 0; i < TET_SIZE - 1; i++) {
    MoreGameInfo->tet[1][i] = 1;
  }
  MoreGameInfo->tet[0][2] = 1;  // L
  MoreGameInfo->tet_type = 'L';
  MoreGameInfo->tet_y = 5;
  tet_rotate(MoreGameInfo);
  tet_rotate(MoreGameInfo);
  tet_rotate(MoreGameInfo);
  MoreGameInfo->tet_x = 9;
  rotate_check(MoreGameInfo);
  ck_assert_int_eq(MoreGameInfo->Input, Action);
  ck_assert_int_eq(MoreGameInfo->Status, GAMING);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(sides_check_test1) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  MoreGameInfo->Status = GAMING;
  for (int i = 0; i < TET_SIZE; i++) {
    for (int j = 0; j < TET_SIZE; j++) {
      MoreGameInfo->tet[i][j] = 0;
    }
  }
  for (int i = 0; i < TET_SIZE - 1; i++) {
    MoreGameInfo->tet[1][i] = 1;
  }
  MoreGameInfo->tet[0][2] = 1;  // L
  MoreGameInfo->tet_type = 'L';
  MoreGameInfo->tet_y = 5;
  MoreGameInfo->tet_x = -1;
  MoreGameInfo->Input = Left;
  sides_check(MoreGameInfo);
  ck_assert_int_eq(MoreGameInfo->Input, Left);
  ck_assert_int_eq(MoreGameInfo->Status, GAMING);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(sides_check_test2) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  MoreGameInfo->Status = GAMING;
  for (int i = 0; i < TET_SIZE; i++) {
    for (int j = 0; j < TET_SIZE; j++) {
      MoreGameInfo->tet[i][j] = 0;
    }
  }
  for (int i = 0; i < TET_SIZE - 1; i++) {
    MoreGameInfo->tet[1][i] = 1;
  }
  MoreGameInfo->tet[0][2] = 1;  // L
  MoreGameInfo->tet_type = 'L';
  MoreGameInfo->tet_y = 5;
  MoreGameInfo->tet_x = 8;
  MoreGameInfo->Input = Right;
  sides_check(MoreGameInfo);
  ck_assert_int_eq(MoreGameInfo->Input, Right);
  ck_assert_int_eq(MoreGameInfo->Status, GAMING);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(down_check_test1) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  MoreGameInfo->Status = GAMING;

  for (int i = 0; i < TET_SIZE; i++) {
    for (int j = 0; j < TET_SIZE; j++) {
      MoreGameInfo->tet[i][j] = 0;
    }
  }
  for (int i = 0; i < TET_SIZE - 1; i++) {
    MoreGameInfo->tet[1][i] = 1;
  }
  MoreGameInfo->tet[0][2] = 1;  // L
  MoreGameInfo->tet_type = 'L';

  MoreGameInfo->tet_y = 19;
  MoreGameInfo->tet_x = 3;
  MoreGameInfo->Input = Down;
  down_check(MoreGameInfo);
  ck_assert_int_eq(MoreGameInfo->Input, Down);
  ck_assert_int_eq(MoreGameInfo->Status, SPAWN);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(user_action_test1) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  int ch = 's';
  user_action(MoreGameInfo, ch);
  ck_assert_int_eq(MoreGameInfo->Input, Start);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(user_action_test2) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  int ch = 'p';
  user_action(MoreGameInfo, ch);
  ck_assert_int_eq(MoreGameInfo->Status, START);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(user_action_test3) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  int ch = 'p';
  MoreGameInfo->first_time = FALSE;
  user_action(MoreGameInfo, ch);
  ck_assert_int_eq(MoreGameInfo->Status, PAUSE);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(user_action_test4) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  int ch = 'p';
  MoreGameInfo->first_time = FALSE;
  MoreGameInfo->Status = PAUSE;
  user_action(MoreGameInfo, ch);
  ck_assert_int_eq(MoreGameInfo->Status, START);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(user_action_test5) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  int ch = 'q';
  user_action(MoreGameInfo, ch);
  ck_assert_int_eq(MoreGameInfo->Status, TERMINATE);
  ck_assert_int_eq(MoreGameInfo->Input, Terminate);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(user_action_test6) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  int ch = 0404;  // KEY_LEFT
  user_action(MoreGameInfo, ch);
  ck_assert_int_eq(MoreGameInfo->Input, Left);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(user_action_test7) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  int ch = 0405;  // KEY_RIGHT
  user_action(MoreGameInfo, ch);
  ck_assert_int_eq(MoreGameInfo->Input, Right);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(user_action_test8) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  int ch = 0402;  // KEY_DOWN
  user_action(MoreGameInfo, ch);
  ck_assert_int_eq(MoreGameInfo->Input, Down);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(user_action_test9) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  int ch = 'e';
  user_action(MoreGameInfo, ch);
  ck_assert_int_eq(MoreGameInfo->Input, Action);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(user_action_test10) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  int ch = 0403;  // KEY_UP
  user_action(MoreGameInfo, ch);
  ck_assert_int_eq(MoreGameInfo->Input, Up);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(user_action_test11) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  int ch = 'Z';
  user_action(MoreGameInfo, ch);
  ck_assert_int_eq(MoreGameInfo->Input, Up);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(userInput_test1) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  UserAction_t user_input = Up;
  userInput(user_input, false);
  ck_assert_int_eq(MoreGameInfo->Input, Up);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(updateCurrentState_test1) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  MoreGameInfo->Input = Down;
  updateCurrentState(MoreGameInfo);
  ck_assert_int_eq(MoreGameInfo->Status, GAMING);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(updateCurrentState_test2) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  write_high_score(1000);
  MoreGameInfo->Input = Down;
  MoreGameInfo->GameInfo->score = 1001;
  updateCurrentState(MoreGameInfo);
  ck_assert_int_eq(MoreGameInfo->Status, GAMING);
  write_high_score(1000);
  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(collision_check_test1) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  MoreGameInfo->Status = GAMING;
  for (int i = 0; i < TET_SIZE; i++) {
    for (int j = 0; j < TET_SIZE; j++) {
      MoreGameInfo->tet[i][j] = 0;
    }
  }
  for (int i = 0; i < TET_SIZE - 1; i++) {
    MoreGameInfo->tet[1][i] = 1;
  }
  MoreGameInfo->tet[0][2] = 1;  // L
  MoreGameInfo->tet_type = 'L';
  MoreGameInfo->tet_y = 1;
  for (int i = 0; i < COLUMNS; i++) {
    MoreGameInfo->GameInfo->field[1][i] = 1;
  }

  collision_check(MoreGameInfo);
  ck_assert_int_eq(MoreGameInfo->Status, GAMEOVER);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(tet_rotate_test1) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  MoreGameInfo->Status = GAMING;
  for (int i = 0; i < TET_SIZE; i++) {
    for (int j = 0; j < TET_SIZE; j++) {
      MoreGameInfo->tet[i][j] = 0;
    }
  }
  for (int i = 0; i < TET_SIZE - 1; i++) {
    MoreGameInfo->tet[1][i] = 1;
  }
  MoreGameInfo->tet[0][1] = 1;
  MoreGameInfo->tet_type = 'T';

  MoreGameInfo->tet_y = 5;

  tet_rotate(MoreGameInfo);

  ck_assert_int_eq(MoreGameInfo->tet[2][1], 1);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(tet_rotate_test2) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  MoreGameInfo->Status = GAMING;
  for (int i = 0; i < TET_SIZE; i++) {
    for (int j = 0; j < TET_SIZE; j++) {
      MoreGameInfo->tet[i][j] = 0;
    }
  }
  MoreGameInfo->tet[0][1] = 1;
  MoreGameInfo->tet[0][2] = 1;
  MoreGameInfo->tet[1][0] = 1;
  MoreGameInfo->tet[1][1] = 1;
  MoreGameInfo->tet_type = 'S';

  MoreGameInfo->tet_y = 5;

  tet_rotate(MoreGameInfo);

  ck_assert_int_eq(MoreGameInfo->tet[2][2], 1);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(tet_rotate_test3) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  MoreGameInfo->Status = GAMING;
  for (int i = 0; i < TET_SIZE; i++) {
    for (int j = 0; j < TET_SIZE; j++) {
      MoreGameInfo->tet[i][j] = 0;
    }
  }

  MoreGameInfo->tet[0][0] = 1;
  MoreGameInfo->tet[0][1] = 1;
  MoreGameInfo->tet[1][1] = 1;
  MoreGameInfo->tet[1][2] = 1;
  MoreGameInfo->tet_type = 'Z';

  MoreGameInfo->tet_y = 5;

  tet_rotate(MoreGameInfo);
  tet_rotate(MoreGameInfo);

  ck_assert_int_eq(MoreGameInfo->tet[0][0], 1);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(tet_rotate_test4) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  MoreGameInfo->Status = GAMING;
  for (int i = 0; i < TET_SIZE; i++) {
    for (int j = 0; j < TET_SIZE; j++) {
      MoreGameInfo->tet[i][j] = 0;
    }
  }
  MoreGameInfo->tet[0][1] = 1;
  MoreGameInfo->tet[0][2] = 1;
  MoreGameInfo->tet[1][0] = 1;
  MoreGameInfo->tet[1][1] = 1;
  MoreGameInfo->tet_type = 'S';

  MoreGameInfo->tet_y = 5;

  tet_rotate(MoreGameInfo);
  tet_rotate(MoreGameInfo);

  ck_assert_int_eq(MoreGameInfo->tet[0][2], 1);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(tet_rotate_test5) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  MoreGameInfo->Status = GAMING;
  for (int i = 0; i < TET_SIZE; i++) {
    for (int j = 0; j < TET_SIZE; j++) {
      MoreGameInfo->tet[i][j] = 0;
    }
  }

  for (int i = 0; i < TET_SIZE; i++) {
    MoreGameInfo->tet[0][i] = 1;
  }
  MoreGameInfo->tet_type = 'I';

  MoreGameInfo->tet_y = 5;

  tet_rotate(MoreGameInfo);

  ck_assert_int_eq(MoreGameInfo->tet[1][2], 1);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(tet_rotate_test6) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  MoreGameInfo->Status = GAMING;
  for (int i = 0; i < TET_SIZE; i++) {
    for (int j = 0; j < TET_SIZE; j++) {
      MoreGameInfo->tet[i][j] = 0;
    }
  }

  for (int i = 0; i < TET_SIZE; i++) {
    MoreGameInfo->tet[0][i] = 1;
  }
  MoreGameInfo->tet_type = 'I';

  MoreGameInfo->tet_y = 5;

  tet_rotate(MoreGameInfo);
  tet_rotate(MoreGameInfo);

  ck_assert_int_eq(MoreGameInfo->tet[0][0], 1);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(del_line_check_test1) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);
  MoreGameInfo->Status = GAMING;

  for (int i = 0; i < COLUMNS; i++) {
    MoreGameInfo->GameInfo->field[10][i] = 1;
  }

  int check = del_line_check(MoreGameInfo);

  ck_assert_int_eq(check, 1);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(rows_to_points_test1) {
  int rows = 1;
  int check = rows_to_points(rows);
  ck_assert_int_eq(check, 100);
}

START_TEST(rows_to_points_test2) {
  int rows = 2;
  int check = rows_to_points(rows);
  ck_assert_int_eq(check, 300);
}

START_TEST(rows_to_points_test3) {
  int rows = 3;
  int check = rows_to_points(rows);
  ck_assert_int_eq(check, 700);
}

START_TEST(rows_to_points_test4) {
  int rows = 4;
  int check = rows_to_points(rows);
  ck_assert_int_eq(check, 1500);
}
END_TEST

START_TEST(update_speed_test1) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);

  MoreGameInfo->GameInfo->score = 7000;
  update_speed(MoreGameInfo);

  ck_assert_int_eq(MoreGameInfo->GameInfo->speed, 10);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(random_next_tet_test1) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);

  usleep(1000000);

  random_next_tet(MoreGameInfo);

  ck_assert_int_eq(MoreGameInfo->Status, START);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(random_next_tet_test2) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);

  usleep(1000000);

  random_next_tet(MoreGameInfo);

  ck_assert_int_eq(MoreGameInfo->Status, START);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(random_next_tet_test3) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);

  usleep(1000000);

  random_next_tet(MoreGameInfo);

  ck_assert_int_eq(MoreGameInfo->Status, START);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(random_next_tet_test4) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);

  usleep(1000000);

  random_next_tet(MoreGameInfo);

  ck_assert_int_eq(MoreGameInfo->Status, START);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(random_next_tet_test5) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);

  usleep(1000000);

  random_next_tet(MoreGameInfo);

  ck_assert_int_eq(MoreGameInfo->Status, START);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(random_next_tet_test6) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);

  usleep(1000000);

  random_next_tet(MoreGameInfo);

  ck_assert_int_eq(MoreGameInfo->Status, START);

  free_more_game_info(MoreGameInfo);
}
END_TEST

START_TEST(random_next_tet_test7) {
  MoreGameInfo_t* MoreGameInfo =
      (MoreGameInfo_t*)malloc(sizeof(MoreGameInfo_t));
  init_more_game_info(MoreGameInfo);

  usleep(1000000);

  random_next_tet(MoreGameInfo);

  ck_assert_int_eq(MoreGameInfo->Status, START);

  free_more_game_info(MoreGameInfo);
}
END_TEST

Suite* s21_tetris_suite(void) {
  Suite* s = suite_create("s21_tetris_suite");
  TCase* tc = tcase_create("s21_tetris_tc");

  tcase_add_test(tc, iteration_runner_test1);
  tcase_add_test(tc, iteration_runner_test2);
  tcase_add_test(tc, iteration_runner_test3);
  tcase_add_test(tc, iteration_runner_test4);
  tcase_add_test(tc, iteration_runner_test5);
  tcase_add_test(tc, iteration_runner_test6);
  tcase_add_test(tc, iteration_runner_test7);
  tcase_add_test(tc, iteration_runner_test8);
  tcase_add_test(tc, iteration_runner_test9);
  tcase_add_test(tc, iteration_runner_test10);
  tcase_add_test(tc, rotation_check_test1);
  tcase_add_test(tc, sides_check_test1);
  tcase_add_test(tc, sides_check_test2);
  tcase_add_test(tc, down_check_test1);
  tcase_add_test(tc, user_action_test1);
  tcase_add_test(tc, user_action_test2);
  tcase_add_test(tc, user_action_test3);
  tcase_add_test(tc, user_action_test4);
  tcase_add_test(tc, user_action_test5);
  tcase_add_test(tc, user_action_test6);
  tcase_add_test(tc, user_action_test7);
  tcase_add_test(tc, user_action_test8);
  tcase_add_test(tc, user_action_test9);
  tcase_add_test(tc, user_action_test10);
  tcase_add_test(tc, user_action_test11);
  tcase_add_test(tc, userInput_test1);
  tcase_add_test(tc, updateCurrentState_test1);
  tcase_add_test(tc, updateCurrentState_test2);
  tcase_add_test(tc, collision_check_test1);
  tcase_add_test(tc, tet_rotate_test1);
  tcase_add_test(tc, tet_rotate_test2);
  tcase_add_test(tc, tet_rotate_test3);
  tcase_add_test(tc, tet_rotate_test4);
  tcase_add_test(tc, tet_rotate_test5);
  tcase_add_test(tc, tet_rotate_test6);
  tcase_add_test(tc, del_line_check_test1);
  tcase_add_test(tc, rows_to_points_test1);
  tcase_add_test(tc, rows_to_points_test2);
  tcase_add_test(tc, rows_to_points_test3);
  tcase_add_test(tc, rows_to_points_test4);
  tcase_add_test(tc, update_speed_test1);
  tcase_add_test(tc, random_next_tet_test1);
  tcase_add_test(tc, random_next_tet_test2);
  tcase_add_test(tc, random_next_tet_test3);
  tcase_add_test(tc, random_next_tet_test4);
  tcase_add_test(tc, random_next_tet_test5);
  tcase_add_test(tc, random_next_tet_test6);
  tcase_add_test(tc, random_next_tet_test7);

  suite_add_tcase(s, tc);
  return s;
}
void run_test(Suite* test) {
  SRunner* sr = srunner_create(test);
  printf("\n");
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
}

int main() { run_test(s21_tetris_suite()); }

#endif
