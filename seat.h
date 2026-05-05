#ifndef SEAT_H
#define SEAT_H

#include <semaphore.h>

#define ROWS 10
#define COLS 15

typedef struct {
int row;
int col;
int owner;
sem_t lock;
} Seat;

void init_cinema(Seat cinema[ROWS][COLS]);
int reserve_seat(Seat cinema[ROWS][COLS], int row, int col, int user_id);
void print_cinema(Seat cinema[ROWS][COLS]);
void destroy_cinema(Seat cinema [ROWS][COLS]);

#endif // SEAT_H
