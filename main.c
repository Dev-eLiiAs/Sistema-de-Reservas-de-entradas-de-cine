#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "seat.h"
#define NUM_USERS 50
#define ATTEMPTS_PER_USER 5
static Seat cinema[ROWS][COLS];
sem_t mutex;
void *user_thread(void *arg) {
int user_id = *(int *)arg;
free(arg);
for (int k = 0; k < ATTEMPTS_PER_USER; ++k) {
int r = rand() % ROWS;
int c = rand() % COLS;
if (reserve_seat(cinema, r, c, user_id, &mutex)) {
printf("Usuario %d reservó asiento (%d,%d)\n", user_id, r, c);
} else {
printf("Usuario %d falló al reservar (%d,%d) — ocupado\n", user_id, r, c);
}
}
return NULL;
}
int main() {
init_cinema(cinema);
srand(time(NULL));
sem_init(&mutex, 0, 1);
pthread_t threads[NUM_USERS];
for (int i = 0; i < NUM_USERS; ++i) {
int *uid = malloc(sizeof(int));
*uid = i + 1;
pthread_create(&threads[i], NULL, user_thread, uid);
}
for (int i = 0; i < NUM_USERS; ++i)
pthread_join(threads[i], NULL);
print_cinema(cinema);
sem_destroy(&mutex);
return 0;
}
