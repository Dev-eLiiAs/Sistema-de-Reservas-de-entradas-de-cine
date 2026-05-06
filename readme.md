
# Sistema de Reservas de Cine Concurrente (Linux)

Este proyecto consiste en una simulación multihilo desarrollada en lenguaje C que modela un sistema de reserva de asientos para una sala de cine. Utiliza la biblioteca `pthread` para gestionar usuarios concurrentes y semáforos (`sem_t`) bajo el estándar POSIX para garantizar la exclusión mutua y evitar condiciones de carrera.

## Requisitos del Sistema

Para compilar y ejecutar este programa en tu terminal o VM de Linux, es necesario contar con el compilador `gcc` y las herramientas de desarrollo esenciales:
```bash
sudo apt update
sudo apt install build-essential
```

## Estructura del Proyecto

El código se organiza en los siguientes archivos:

*   **`main.c`**: Contiene el punto de entrada, la lógica de creación de hilos (usuarios) y la gestión de métricas de la simulación.
*   **`cinema.c`**: Implementa las funciones de gestión de la sala, incluyendo la inicialización de asientos, la lógica de reserva protegida por semáforos y la representación visual por pantalla.
*   **`seat.h`**: Define la estructura de datos `Seat` y las constantes de dimensiones de la sala (10 filas x 15 columnas).

## Instrucciones de Compilación

En entornos Linux, es fundamental enlazar la librería de hilos durante la compilación. Ejecuta el siguiente comando en tu terminal:
```bash
gcc main.c cinema.c -o cinema -pthread
```

*   `-o cinema`: Define el nombre del ejecutable binario.
*   `-pthread`: Habilita el soporte para hilos y semáforos de la librería `pthreads`.

## Ejecución y Uso

### Ejecución estándar
Por defecto, el programa simula la actividad de 50 usuarios:
```bash
./cinema
```

### Ejecución con parámetros
Puedes especificar el número de usuarios que deseas simular pasando el valor como argumento:
```bash
./cinema 15
./cinema 150
.cinema X
```

## Características Técnicas

*   **Exclusión de Grano Fino**: Se implementa un semáforo independiente por cada asiento de la sala, permitiendo que varios hilos reserven diferentes butacas al mismo tiempo sin bloquearse entre sí.
*   **Seguridad de Hilos (Thread-Safety)**: El generador de números aleatorios está protegido por un semáforo global (`rand_lock`) para asegurar la integridad de las peticiones.
*   **Interfaz Visual**: El estado final de la ocupación se imprime en la terminal utilizando códigos de colores ANSI para identificar los asientos ocupados por cada usuario.

## Notas de Compatibilidad
*   **Binarios**: El archivo `cinema.exe` presente en el repositorio es un ejecutable de Windows y no funcionará en Linux. Siempre debe generarse el binario localmente mediante `gcc`.
*   **Permisos**: Si tras compilar recibes un error de "Permiso denegado", ejecuta `chmod +x cinema`.
