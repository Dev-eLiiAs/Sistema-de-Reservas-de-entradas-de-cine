# Simulador de Reservas de Cine Concurrente

Este proyecto es una simulación multihilo escrita en C que modela un sistema de reserva de asientos de cine. Utiliza la biblioteca `pthread` para simular usuarios concurrentes y semáforos (`sem_t`) para garantizar la exclusión mutua y evitar condiciones de carrera.

## Características Principales

*  **Exclusión Mutua de Grano Fino:** Se ha implementado un semáforo independiente por cada asiento (`cinema[row][col].lock`). Esto permite que múltiples usuarios reserven asientos distintos al mismo tiempo sin bloquear toda la sala, maximizando el rendimiento.
*  **Generador Aleatorio Seguro (Thread-Safe):** La función nativa `rand()` se ha protegido con un semáforo global (`rand_lock`) para evitar colisiones entre hilos al generar las peticiones, solucionando los problemas de concurrencia en entornos Windows.
*  **Métricas Detalladas:** Al finalizar la simulación, el sistema genera un reporte con el tiempo exacto de ejecución, el total de peticiones procesadas y un desglose por usuario indicando qué coordenadas exactas ha comprado (Ej: A15, H5).
*  **Interfaz Visual:** Representación en consola de la matriz de la sala (10x15) con cabeceras de filas/columnas y colores ANSI para identificar visualmente las compras de los distintos usuarios.

---

## Requisitos Previos

Para poder compilar y ejecutar este código, necesitas tener instalado un compilador de C que soporte la librería POSIX Threads (`pthread`). 
*   **En Windows:** Se recomienda usar **MinGW / GCC**.
*   **En Linux:** Paquete `build-essential` (`gcc`).

---

## Cómo compilar y ejecutar el código

Abre una terminal (PowerShell, CMD o bash) en la carpeta donde se encuentran los archivos fuente (`main.c`, `cinema.c`, `seat.h`) y sigue estos pasos:

### 1. Compilar el programa
Ejecuta el siguiente comando para compilar el código. Esto unirá los archivos y generará un ejecutable llamado `cinema_sim.exe`:

```bash
gcc -Wall -pthread -o cinema_sim.exe main.c cinema.c
