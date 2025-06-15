#ifndef FSM_H
#define FSM_H

#include "tetris.h"
#include "tetris_backend.h"

// Две функции, в основном отвечающие за переключение состояний fsm
void iteration_runner(MoreGameInfo_t *MoreGameInfo);
void user_action(MoreGameInfo_t *MoreGameInfo, int user_input);

void down_check(MoreGameInfo_t *MoreGameInfo);
void sides_check(MoreGameInfo_t *MoreGameInfo);
void rotate_check(MoreGameInfo_t *MoreGameInfo);

#endif