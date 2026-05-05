#include <stdio.h>
#include <stdlib.h>
#include "seat.h"

// Inicializamos la sala y preparamos los semaforos de los asientos

void init_cinema(Seat cinema[ROWS][COLS]){
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            cinema[i][j].row = i;
            cinema[i][j].col = j;
            cinema[i][j].owner = -1; // -1 == libre

            // inicializo el semaforo del asiento a 1 (disponible)
            sem_init(&cinema[i][j].lock, 0, 1);
        }
    }
}

// Intento de reservar asiento garantizando la exclusion mutua
int reserve_seat(Seat cinema[ROWS][COLS], int row, int col, int user_id) {
    int success = 0;
    
    // BLOQUEO
    sem_wait(&cinema[row][col].lock);

    // SECCIÓN CRÍTICA
    if (cinema[row][col].owner == -1) {
        cinema[row][col].owner = user_id;
        success = 1;
    }

    // DESBLOQUEO
    sem_post(&cinema[row][col].lock);

    return success;
} 

    // Imprime la cuadrícula visual de la sala
  // Imprime la cuadrícula visual de la sala con coordenadas y colores
void print_cinema(Seat cinema[ROWS][COLS]) {
    printf("\nEstado final de la sala:\n");
    
    // 1. Imprimir la cabecera de las columnas (1 al 15)
    printf("   "); // Espacio para alinear con las letras de las filas
    for (int j = 0; j < COLS; ++j) {
        printf("%2d ", j + 1); // %2d asegura que los números de 2 cifras queden alineados
    }
    printf("\n");

    // 2. Imprimir cada fila
    for (int i = 0; i < ROWS; ++i) {
        // Imprimir la letra de la fila (A, B, C...)
        printf("%c  ", 'A' + i);
        
        for (int j = 0; j < COLS; ++j) {
            if (cinema[i][j].owner == -1) {
                // Asiento libre: Lo pintamos normal (blanco/gris)
                printf(" O ");
            } else {
                // Asiento ocupado: Elegimos un color basado en el ID del usuario
                // Los colores ANSI básicos van del 31 (Rojo) al 36 (Cian)
                int color = 31 + (cinema[i][j].owner % 6);
                
                // \033[%dm cambia el color, \033[0m lo resetea a la normalidad
                printf("\033[%dm X \033[0m", color);
            }
        }
        printf("\n"); // Salto de línea al terminar la fila
    }
}

    // Limpia los recursos del sistema operativo 
    void destroy_cinema(Seat cinema[ROWS][COLS])
    {
        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < COLS; ++j)
            {
                sem_destroy(&cinema[i][j].lock);
            }
        }
    }