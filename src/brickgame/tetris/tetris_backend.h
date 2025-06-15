#ifndef TETRRIS_BACKEND_H
#define TETRRIS_BACKEND_H

#include "tetris.h"

#define ROWS 20
#define COLUMNS 10
#define TET_SIZE 4

int **mem_alloc(int rows, int columns);

void init_more_game_info(MoreGameInfo_t *MoreGameInfo);

void free_more_game_info(MoreGameInfo_t *MoreGameInfo);
void free_matrix(int **matrix, int rows);

void random_next_tet(MoreGameInfo_t *MoreGameInfo);
void tet_generator(MoreGameInfo_t *MoreGameInfo);

MoreGameInfo_t *get_current_game_more_game_info();

void tet_move_down(MoreGameInfo_t *MoreGameInfo);
void tet_move_up(MoreGameInfo_t *MoreGameInfo);
void tet_move_left(MoreGameInfo_t *MoreGameInfo);
void tet_move_right(MoreGameInfo_t *MoreGameInfo);

void make_tet_field(MoreGameInfo_t *MoreGameInfo);
void set_tet(MoreGameInfo_t *MoreGameInfo);
void spawn_new_tet(MoreGameInfo_t *MoreGameInfo);

void tet_rotate(MoreGameInfo_t *MoreGameInfo);
void rotate_clockwise(MoreGameInfo_t *MoreGameInfo);
void adjust_rotation(MoreGameInfo_t *MoreGameInfo, int adjust);

int del_line_check(MoreGameInfo_t *MoreGameInfo);
int full_row_check(MoreGameInfo_t *MoreGameInfo, int row);
void del_line(MoreGameInfo_t *MoreGameInfo, int row);
void move_lines_down(MoreGameInfo_t *MoreGameInfo, int row);

int rows_to_points(int rows);
int read_high_score();
void write_high_score(int score);
void update_speed(MoreGameInfo_t *MoreGameInfo);

int collision_check(MoreGameInfo_t *MoreGameInfo);
int boundaries_check(int row, int col, int ty, int tx);

#endif