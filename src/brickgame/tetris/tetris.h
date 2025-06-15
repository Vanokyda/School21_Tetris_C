#ifndef TETRIS_H
#define TETRIS_H

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Defines used in adjusting tetromino after roatation
 */
#define LEFT 0
#define UP 1

/**
 * Represents different player actions in the game
 */
typedef enum UserAction_t {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

/**
 * Structure proveided in the task
 * @param field      Holds current state of the game field
 * @param next       Holds next tetromino
 * @param score      Score of the current game
 * @param high_score High score
 * @param level      Level (affects speed)
 * @param speed      Speed of the game
 * @param pause      If the game is paused
 */
typedef struct GameInfo_t {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

/**
 * Represents different game states
 */
typedef enum GameState_t {
  START,
  PAUSE,
  TERMINATE,
  SPAWN,
  GAMING,
  GAMEOVER
} GameState_t;

/**
 * Extencion of the structure provided in the task
 * @param GameInfo   A pointer to the GameInfo_t struct
 * @param Input      The action performed by the user
 * @param Status     The current state of the game
 * @param tet        A pointer to the current tetromino
 * @param tet_x      The x coordinate of the top_left corner of the current
 * tetromino
 * @param tet_y      The y coordinate of the top_left corner of the current
 * tetromino
 * @param first_time If it is the first time the game is played (for start
 * screen)
 * @param Count      Number of iterations passed after tetromino moved down
 * @param tet_type   The type of the current tetromino
 * @param next_tet_type The type of the next tetromino
 * @param colour     The colour of the current tetromino
 * @param next_colour The colour of the next tetromino
 */
typedef struct MoreGameInfo_t {
  GameInfo_t *GameInfo;
  UserAction_t Input;
  GameState_t Status;
  int **tet;
  int tet_x;
  int tet_y;
  bool first_time;
  int Count;
  char tet_type;
  char next_tet_type;
  int colour;
  int next_colour;
} MoreGameInfo_t;

void userInput(UserAction_t user_input, bool hold);

GameInfo_t *updateCurrentState(MoreGameInfo_t *MoreGameInfo);

#endif
