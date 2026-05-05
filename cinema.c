#include <stdio.h>
#include <stdlib.h>
#include "seat.h"

void init_cinema(Seat cinema[ROWS][COLS]) {
for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
        cinema[i][j].row = i;
        cinema[i][j].col = j;
        cinema[i][j].owner = -1;
    }
}
}

int reserve_seat(Seat cinema[ROWS][COLS], int row, int col, int user_id, sem_t *mutex) {
sem_wait(mutex);
int success = 0;
if (cinema[row][col].owner == -1) {
    cinema[row][col].owner = user_id;
    success = 1;
}
sem_post(mutex);
return success;
}

void print_cinema(Seat cinema[ROWS][COLS]) {
printf("\nEstado final de la sala:\n");
for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
        printf("%c ", cinema[i][j].owner == -1 ? 'O' : 'X');
    }
    printf("\n");
}
}
