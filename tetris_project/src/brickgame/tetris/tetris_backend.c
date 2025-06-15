#include "tetris_backend.h"

#include <time.h>

#include "tetris.h"

/** Returns a pointer to the MoreGameInfo_t structure containing information
 * about the current game.
 *
 * @return A pointer to the MoreGameInfo_t structure. */
MoreGameInfo_t *get_current_game_more_game_info() {
  static MoreGameInfo_t MoreGameInfo = {0};
  return &MoreGameInfo;
}

/** Initializes the MoreGameInfo_t structure with the necessary information for
 * a game.
 * @param MoreGameInfo A pointer to the MoreGameInfo_t structure.
 *
 * @return void */
void init_more_game_info(MoreGameInfo_t *MoreGameInfo) {
  MoreGameInfo->GameInfo = (GameInfo_t *)malloc(sizeof(GameInfo_t));
  MoreGameInfo->GameInfo->field = mem_alloc(ROWS, COLUMNS);
  MoreGameInfo->GameInfo->next = mem_alloc(TET_SIZE, TET_SIZE);
  random_next_tet(MoreGameInfo);
  MoreGameInfo->tet = mem_alloc(TET_SIZE, TET_SIZE);
  set_tet(MoreGameInfo);
  MoreGameInfo->tet_x = 3;
  MoreGameInfo->tet_y = 0;
  MoreGameInfo->GameInfo->score = 0;
  MoreGameInfo->GameInfo->high_score = read_high_score();
  MoreGameInfo->GameInfo->level = 0;
  MoreGameInfo->GameInfo->speed = 0;
  MoreGameInfo->GameInfo->pause = -1;
  MoreGameInfo->Input = Up;
  MoreGameInfo->Status = START;
  MoreGameInfo->first_time = 1;
  MoreGameInfo->Count = 1;
}

/**
 * Allocates memory for a 2D array of integers.
 *
 * @param rows The number of rows in the array.
 * @param columns The number of columns in the array.
 *
 * @return A pointer to the allocated 2D array.
 */
int **mem_alloc(int rows, int columns) {
  int **matrix = (int **)calloc(rows, sizeof(int *));
  for (int i = 0; i < rows; i++) {
    matrix[i] = (int *)calloc(columns, sizeof(int));
  }
  return matrix;
}

/**
 * Frees a dynamically allocated 2D integer array.
 *
 * @param matrix The pointer to the array to be freed.
 * @param rows The number of rows in the array.
 *
 * @return void
 */
void free_matrix(int **matrix, int rows) {
  for (int i = 0; i < rows; i++) {
    free(matrix[i]);
  }
  free(matrix);
}

/**
 * Checks for collisions between the tetromino and the game field.
 *
 * @param MoreGameInfo a pointer to the MoreGameInfo_t structure
 *                    containing information about the game state
 *
 * @return int flag indicating whether a collision occurred
 *         (1 if a collision occurred, 0 otherwise)
 */
int collision_check(MoreGameInfo_t *MoreGameInfo) {
  int flag = 0;
  int ty = MoreGameInfo->tet_y;
  int tx = MoreGameInfo->tet_x;

  int **tetromino = MoreGameInfo->tet;
  int **field = MoreGameInfo->GameInfo->field;

  for (int row = 0; row < TET_SIZE && flag == 0; row++) {
    for (int col = 0; col < TET_SIZE && flag == 0; col++) {
      int fgr = tetromino[row][col];

      if (fgr == 1) {
        // Проверка на столкновение с границами
        if (boundaries_check(row, col, ty, tx)) {
          flag = 1;
          // Проверка на столкновение с полем
        } else if (field[ty + row][tx + col] == 1) {
          // Если столкновение произошло вверху экрана, то
          // гейм овер :(
          if (ty + row <= 1) {
            MoreGameInfo->Status = GAMEOVER;
          }
          flag = 1;
        }
      }
    }
  }
  return flag;
}

/**
 * Checks if the given coordinates are within the boundaries of the game field.
 *
 * @param row The row index of the coordinate.
 * @param col The column index of the coordinate.
 * @param ty The row index of the top-left corner of the tetromino.
 * @param tx The column index of the top-left corner of the tetromino.
 *
 * @return 1 if the coordinates are outside the boundaries, 0 otherwise.
 */
int boundaries_check(int row, int col, int ty, int tx) {
  int result = 0;
  if (row + ty == ROWS || col + tx < 0 || col + tx == COLUMNS) result = 1;
  return result;
}

/**
 * Frees the memory allocated for the MoreGameInfo_t structure and its
 * components.
 *
 * @param MoreGameInfo pointer to the MoreGameInfo_t structure to be freed
 *
 * @return void
 */
void free_more_game_info(MoreGameInfo_t *MoreGameInfo) {
  free_matrix(MoreGameInfo->GameInfo->field, ROWS);
  free_matrix(MoreGameInfo->GameInfo->next, TET_SIZE);
  free_matrix(MoreGameInfo->tet, TET_SIZE);
  free(MoreGameInfo->GameInfo);
  free(MoreGameInfo);
}

/**
 * Moves the tetromino down by one unit by substracting 1 from tet_y value
 *
 * @param MoreGameInfo Pointer to the MoreGameInfo_t structure.
 *
 * @return void
 */
void tet_move_down(MoreGameInfo_t *MoreGameInfo) { MoreGameInfo->tet_y++; }

/**
 * Moves the tetromino up by one unit by adding 1 to tet_y value
 *
 * @param MoreGameInfo Pointer to the MoreGameInfo_t structure.
 *
 * @return void
 */
void tet_move_up(MoreGameInfo_t *MoreGameInfo) { MoreGameInfo->tet_y--; }

/**
 * Moves the tetromino left by one unit by substracting 1 from tet_x value
 *
 * @param MoreGameInfo Pointer to the MoreGameInfo_t structure.
 *
 * @return void
 */
void tet_move_left(MoreGameInfo_t *MoreGameInfo) { MoreGameInfo->tet_x--; }

/**
 * Moves the tetromino right by one unit by adding 1 to tet_x value
 *
 * @param MoreGameInfo Pointer to the MoreGameInfo_t structure.
 *
 * @return void
 */
void tet_move_right(MoreGameInfo_t *MoreGameInfo) { MoreGameInfo->tet_x++; }

/**
 * Rotates the tetromino in the game.
 *
 * @param MoreGameInfo a pointer to the MoreGameInfo_t structure
 *
 * @return void
 */
void tet_rotate(MoreGameInfo_t *MoreGameInfo) {
  if (MoreGameInfo->tet_type == 'J' || MoreGameInfo->tet_type == 'L' ||
      MoreGameInfo->tet_type == 'T') {
    rotate_clockwise(MoreGameInfo);
    adjust_rotation(MoreGameInfo, LEFT);
  } else if (MoreGameInfo->tet_type == 'S' || MoreGameInfo->tet_type == 'Z') {
    rotate_clockwise(MoreGameInfo);
    adjust_rotation(MoreGameInfo, LEFT);
    if ((MoreGameInfo->tet[2][0] && MoreGameInfo->tet_type == 'S') ||
        (MoreGameInfo->tet[2][2] && MoreGameInfo->tet_type == 'Z')) {
      adjust_rotation(MoreGameInfo, UP);
    }
  } else if (MoreGameInfo->tet_type == 'I') {
    rotate_clockwise(MoreGameInfo);
    if (MoreGameInfo->tet[0][3]) {
      adjust_rotation(MoreGameInfo, LEFT);
    }
    if (MoreGameInfo->tet[2][0]) {
      adjust_rotation(MoreGameInfo, UP);
      adjust_rotation(MoreGameInfo, UP);
    }
  }
}

/**
 * Adjusts the rotation of the tetromino in the game.
 * Complimentary function of tet_rotate
 *
 * @param MoreGameInfo a pointer to the MoreGameInfo_t structure
 * @param adjust the adjustment to be made to the rotation (LEFT or UP)
 *
 * @return void
 *
 */
void adjust_rotation(MoreGameInfo_t *MoreGameInfo, int adjust) {
  int tmp[TET_SIZE][TET_SIZE] = {0};
  int tmp2[TET_SIZE][TET_SIZE] = {0};

  for (int i = 0; i < TET_SIZE; i++) {
    for (int j = 0; j < TET_SIZE; j++) {
      tmp[i][j] = MoreGameInfo->tet[i][j];
    }
  }
  for (int i = 0; i < TET_SIZE; i++) {
    for (int j = 0; j < TET_SIZE; j++) {
      if (adjust == LEFT) {
        if (tmp[i][j]) tmp2[i][j - 1] = tmp[i][j];  // move_left
      } else if (adjust == UP) {
        if (tmp[i][j]) tmp2[i - 1][j] = tmp[i][j];  // move_up
      }
    }
  }
  for (int i = 0; i < TET_SIZE; i++) {
    for (int j = 0; j < TET_SIZE; j++) {
      MoreGameInfo->tet[i][j] = tmp2[i][j];
    }
  }
}

/**
 * Rotates the tetromino in the game clockwise.
 * Complimentary function of tet_rotate
 *
 * @param MoreGameInfo a pointer to the MoreGameInfo_t structure
 *
 * @return void
 *
 */
void rotate_clockwise(MoreGameInfo_t *MoreGameInfo) {
  int tmp[TET_SIZE][TET_SIZE] = {0};

  for (int i = 0; i < TET_SIZE; i++) {
    for (int j = 0; j < TET_SIZE; j++) {
      tmp[i][j] = MoreGameInfo->tet[i][j];
    }
  }

  for (int i = 0; i < TET_SIZE / 2; i++) {
    for (int j = i; j < TET_SIZE - i - 1; j++) {
      int temp = tmp[i][j];
      tmp[i][j] = tmp[TET_SIZE - 1 - j][i];
      tmp[TET_SIZE - 1 - j][i] = tmp[TET_SIZE - 1 - i][TET_SIZE - 1 - j];
      tmp[TET_SIZE - 1 - i][TET_SIZE - 1 - j] = tmp[j][TET_SIZE - 1 - i];
      tmp[j][TET_SIZE - 1 - i] = temp;
    }
  }
  for (int i = 0; i < TET_SIZE; i++) {
    for (int j = 0; j < TET_SIZE; j++) {
      MoreGameInfo->tet[i][j] = tmp[i][j];
    }
  }
}

/**
 * Makes tetromino part of the field.
 *
 * @param MoreGameInfo A pointer to a MoreGameInfo_t struct containing
 * information about the game state.
 *
 * @return void
 *
 */
void make_tet_field(MoreGameInfo_t *MoreGameInfo) {
  for (int row = 0; row < TET_SIZE; row++) {
    for (int column = 0; column < TET_SIZE; column++) {
      if (MoreGameInfo->tet[row][column] == 1) {
        MoreGameInfo->GameInfo
            ->field[MoreGameInfo->tet_y + row][MoreGameInfo->tet_x + column] =
            1;
      }
    }
  }
}

/**
 * Checks for full rows in the game field and deletes them, moving the remaining
 * lines down. Returns the number of deleted lines.
 *
 * @param MoreGameInfo A pointer to a MoreGameInfo_t struct containing
 * information about the game state.
 *
 * @return The number of deleted lines.
 */
int del_line_check(MoreGameInfo_t *MoreGameInfo) {
  int count = 0;
  for (int row = 0; row <= ROWS - 1; row++) {
    while (full_row_check(MoreGameInfo, row)) {
      del_line(MoreGameInfo, row);
      move_lines_down(MoreGameInfo, row);
      count++;
    }
  }
  return count;
}

/**
 * Checks if a given row in the game field is full.
 * Complimentary function of del_line_check.
 *
 * @param MoreGameInfo A pointer to a MoreGameInfo_t struct containing
 * information about the game state.
 * @param row The row index to check.
 *
 * @return 1 if the row is full, 0 otherwise.
 */
int full_row_check(MoreGameInfo_t *MoreGameInfo, int row) {
  int check = 1;
  for (int column = 0; column < COLUMNS; column++) {
    if (MoreGameInfo->GameInfo->field[row][column] == 0) {
      check = 0;
    }
  }
  return check;
}

/** Deletes a line in the game field by setting all elements of the specified
 * row to 0.
 * Complimentary function of del_line_check
 *
 * @param MoreGameInfo A pointer to a MoreGameInfo_t struct containing
 * information about the game state.
 * @param row The row index of the line to be deleted.
 *
 * @return void
 */
void del_line(MoreGameInfo_t *MoreGameInfo, int row) {
  for (int column = 0; column < COLUMNS; column++) {
    MoreGameInfo->GameInfo->field[row][column] = 0;
  }
}

/**
 * Moves all lines in the game field down by one row.
 * Complimentary function of del_line_check
 *
 * @param MoreGameInfo A pointer to a MoreGameInfo_t struct containing
 * information about the game state.
 * @param row The row index of the line to be moved.
 *
 * @return void
 */
void move_lines_down(MoreGameInfo_t *MoreGameInfo, int row) {
  for (int i = row; i - 1 >= 0; i--) {
    for (int column = 0; column < COLUMNS; column++) {
      MoreGameInfo->GameInfo->field[i][column] =
          MoreGameInfo->GameInfo->field[i - 1][column];
    }
  }
}

/**
 * Calculates the points based on the number of rows.
 *
 * @param rows The number of rows.
 *
 * @return The corresponding points.
 */
int rows_to_points(int rows) {
  int res = 0;
  if (rows == 1) {
    res = 100;
  } else if (rows == 2) {
    res = 300;
  } else if (rows == 3) {
    res = 700;
  } else if (rows == 4) {
    res = 1500;
  }
  return res;
}

/**
 * Reads the high score from a file.
 *
 * @return The high score read from the file.
 *
 */
int read_high_score() {
  int high_score = 0;
  char fileName[] = "./brickgame/tetris/high_score.txt";
  FILE *file = fopen(fileName, "r");
  if (file != NULL) {
    int ch;
    while ((ch = fgetc(file)) != EOF) {
      if (ch >= '0' && ch <= '9') {
        high_score = high_score * 10 + (ch - '0');
      }
    }
  }
  fclose(file);
  return high_score;
}

/**
 * Writes the given score to a file as the high score.
 *
 * @param score the score to be written as the high score
 *
 * @return void
 *
 */
void write_high_score(int score) {
  char fileName[] = "./brickgame/tetris/high_score.txt";
  FILE *file = fopen(fileName, "w");
  if (file != NULL) {
    fprintf(file, "%d", score);
  }
  fclose(file);
}

/**
 * Updates the speed and level of the game based on the current score.
 *
 * @param MoreGameInfo A pointer to the MoreGameInfo_t structure that contains
 * the game information.
 *
 * @return void
 *
 */
void update_speed(MoreGameInfo_t *MoreGameInfo) {
  MoreGameInfo->GameInfo->level = (int)MoreGameInfo->GameInfo->score / 600;
  MoreGameInfo->GameInfo->speed = MoreGameInfo->GameInfo->level;
  if (MoreGameInfo->GameInfo->speed > 10 ||
      MoreGameInfo->GameInfo->level > 10) {
    MoreGameInfo->GameInfo->speed = 10;
    MoreGameInfo->GameInfo->level = 10;
  }
}

/**
 * Makes next tetromino – current tetromino and generates new next tetromino.
 *
 * @param MoreGameInfo A pointer to the MoreGameInfo_t structure.
 *
 * @return void
 *
 */
void spawn_new_tet(MoreGameInfo_t *MoreGameInfo) {
  free_matrix(MoreGameInfo->tet, TET_SIZE);
  MoreGameInfo->tet = mem_alloc(TET_SIZE, TET_SIZE);
  set_tet(MoreGameInfo);
  MoreGameInfo->tet_x = 3;
  MoreGameInfo->tet_y = 0;
  free_matrix(MoreGameInfo->GameInfo->next, TET_SIZE);
  MoreGameInfo->GameInfo->next = mem_alloc(TET_SIZE, TET_SIZE);
  random_next_tet(MoreGameInfo);
  MoreGameInfo->Status = GAMING;
}

/**
 * Copies the next tetromino from MoreGameInfo->GameInfo->next to
 * MoreGameInfo->tet and sets the tetromino type and color.
 *
 * @param MoreGameInfo a pointer to a MoreGameInfo_t struct containing
 * information about the game state
 *
 * @return void
 */
void set_tet(MoreGameInfo_t *MoreGameInfo) {
  for (int i = 0; i < TET_SIZE; i++) {
    for (int j = 0; j < TET_SIZE; j++) {
      MoreGameInfo->tet[i][j] = MoreGameInfo->GameInfo->next[i][j];
    }
  }
  MoreGameInfo->tet_type = MoreGameInfo->next_tet_type;
  MoreGameInfo->colour = MoreGameInfo->next_colour;
}

/**
 * Generates a random next tetromino and updates the next_tet_type and
 * next_colour fields of the MoreGameInfo struct.
 *
 * @param MoreGameInfo pointer to the MoreGameInfo struct containing the game
 * information
 *
 * @return void
 */
void random_next_tet(MoreGameInfo_t *MoreGameInfo) {
  srand((unsigned)time(NULL));
  int r = rand() % 8;
  r > 0 ? r : r++;
  switch (r) {
    case 1:  // I
      MoreGameInfo->next_tet_type = 'I';
      MoreGameInfo->next_colour = 1;
      tet_generator(MoreGameInfo);
      break;
    case 2:  // O
      MoreGameInfo->next_tet_type = 'O';
      MoreGameInfo->next_colour = 2;
      tet_generator(MoreGameInfo);
      break;
    case 3:  // T
      MoreGameInfo->next_tet_type = 'T';
      MoreGameInfo->next_colour = 4;
      tet_generator(MoreGameInfo);
      break;
    case 4:  // J
      MoreGameInfo->next_tet_type = 'J';
      MoreGameInfo->next_colour = 5;
      tet_generator(MoreGameInfo);
      break;
    case 5:  // L
      MoreGameInfo->next_tet_type = 'L';
      MoreGameInfo->next_colour = 5;
      tet_generator(MoreGameInfo);
      break;
    case 6:  // S
      MoreGameInfo->next_tet_type = 'S';
      MoreGameInfo->next_colour = 3;
      tet_generator(MoreGameInfo);
      break;
    case 7:  // Z
      MoreGameInfo->next_tet_type = 'Z';
      MoreGameInfo->next_colour = 3;
      tet_generator(MoreGameInfo);
      break;
    default:
      break;
  }
}

/**
 * Generates a tetromino based on the type specified in the MoreGameInfo struct
 * and generated in random_next_tet. Complementary to random_next_tet
 *
 * @param MoreGameInfo pointer to the MoreGameInfo_t struct containing the game
 * information
 *
 * @return void
 */
void tet_generator(MoreGameInfo_t *MoreGameInfo) {
  switch (MoreGameInfo->next_tet_type) {
    case 'I':
      for (int i = 0; i < TET_SIZE; i++) {
        MoreGameInfo->GameInfo->next[0][i] = 1;
      }
      break;
    case 'O':
      for (int i = 0; i < 2; i++) {
        for (int j = 1; j < 3; j++) {
          MoreGameInfo->GameInfo->next[i][j] = 1;
        }
      }
      break;
    case 'T':
      for (int i = 0; i < TET_SIZE - 1; i++) {
        MoreGameInfo->GameInfo->next[1][i] = 1;
      }
      MoreGameInfo->GameInfo->next[0][1] = 1;
      break;
    case 'J':
      for (int i = 0; i < TET_SIZE - 1; i++) {
        MoreGameInfo->GameInfo->next[1][i] = 1;
      }
      MoreGameInfo->GameInfo->next[0][0] = 1;
      break;
    case 'L':
      for (int i = 0; i < TET_SIZE - 1; i++) {
        MoreGameInfo->GameInfo->next[1][i] = 1;
      }
      MoreGameInfo->GameInfo->next[0][2] = 1;
      break;
    case 'S':
      MoreGameInfo->GameInfo->next[0][1] = 1;
      MoreGameInfo->GameInfo->next[0][2] = 1;
      MoreGameInfo->GameInfo->next[1][0] = 1;
      MoreGameInfo->GameInfo->next[1][1] = 1;
      break;
    case 'Z':
      MoreGameInfo->GameInfo->next[0][0] = 1;
      MoreGameInfo->GameInfo->next[0][1] = 1;
      MoreGameInfo->GameInfo->next[1][1] = 1;
      MoreGameInfo->GameInfo->next[1][2] = 1;
      break;
    default:
      break;
  }
}
