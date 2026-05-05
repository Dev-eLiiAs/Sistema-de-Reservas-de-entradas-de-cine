#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "seat.h"

#define MAX_ATTEMPTS_PER_USER 5

static Seat cinema[ROWS][COLS];
int *user_attempts_count; 

// NUEVO: Un candado exclusivo para proteger la función rand() de Windows
sem_t rand_lock;

void *user_thread(void *arg) {
    int user_id = *(int *)arg;
    free(arg); 

    // SOLUCIÓN: Inicializamos la semilla interna de ESTE hilo en concreto
    srand(time(NULL) ^ (user_id * 100));

    // Pedimos turno para usar el rand() y decidir cuántas entradas comprar
    sem_wait(&rand_lock);
    int attempts = (rand() % MAX_ATTEMPTS_PER_USER) + 1;
    sem_post(&rand_lock); // Liberamos el turno
    
    user_attempts_count[user_id] = attempts; 

    for (int k = 0; k < attempts; ++k) {
        
        // Pedimos turno otra vez para elegir la fila y columna
        sem_wait(&rand_lock);
        int r = rand() % ROWS;
        int c = rand() % COLS;
        sem_post(&rand_lock); // Liberamos el turno

        // Intentamos reservar la butaca
        reserve_seat(cinema, r, c, user_id); 
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    int num_users = 50; 
    if (argc > 1) {
        num_users = atoi(argv[1]);
        if (num_users <= 0) num_users = 50; 
    }

    user_attempts_count = calloc(num_users + 1, sizeof(int));

    // Inicializamos la semilla general de Windows UNA SOLA VEZ
    srand(time(NULL));
    
    // Inicializamos nuestro nuevo candado para el rand()
    sem_init(&rand_lock, 0, 1);

    printf("Iniciando simulacion con %d usuarios...\n", num_users);

    init_cinema(cinema);
    pthread_t *threads = malloc(num_users * sizeof(pthread_t));

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < num_users; ++i) {
        int *uid = malloc(sizeof(int));
        *uid = i + 1;
        pthread_create(&threads[i], NULL, user_thread, uid);
    }

    for (int i = 0; i < num_users; ++i) {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;

    print_cinema(cinema);
    
    printf("\nMetricas de Rendimiento:\n");
    printf("- Usuarios simulados: %d\n", num_users);
    
    int total_requests = 0;
    
    for(int u = 1; u <= num_users; u++) {
        total_requests += user_attempts_count[u];
        
        int seats_reserved = 0;
        for(int r = 0; r < ROWS; r++) {
            for(int c = 0; c < COLS; c++) {
                if(cinema[r][c].owner == u) seats_reserved++;
            }
        }
        
        printf("- Usuario %d: Asientos: %d", u, seats_reserved);
        
        if (seats_reserved > 0) {
            printf(" (");
            int printed = 0;
            for(int r = 0; r < ROWS; r++) {
                for(int c = 0; c < COLS; c++) {
                    if(cinema[r][c].owner == u) {
                        printf("%c%d", 'A' + r, c + 1); 
                        printed++;
                        if (printed < seats_reserved) printf(", ");
                    }
                }
            }
            printf(")");
        }
        printf("\n");
    }

    printf("- Peticiones totales realizadas: %d\n", total_requests);
    printf("- Tiempo total de ejecucion: %f segundos\n", time_taken);

    // Limpieza final
    destroy_cinema(cinema);
    sem_destroy(&rand_lock); // Destruimos nuestro candado
    free(threads);
    free(user_attempts_count);

    return 0;
}