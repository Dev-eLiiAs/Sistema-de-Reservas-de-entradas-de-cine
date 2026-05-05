# Sistema de Reserva de Entradas de Cine 

**Asignatura:** Sistemas Operativos
**Alumno:** Elías Sánchez Martín 
**Correo:** 22323282@live.uem.es

## Descripción del Proyecto
Este proyecto implementa la simulación de un sistema de reserva de entradas de cine en un entorno concurrente. El objetivo principal es gestionar eficientemente las peticiones simultáneas de múltiples clientes (hilos) intentando reservar asientos compartidos, asegurando la exclusión mutua y previniendo condiciones de carrera mediante el uso de mecanismos de sincronización como semáforos o monitores.

## Objetivos
* **Codificación:** Implementar un sistema de reserva concurrente, empleando semáforos/monitors para proteger los recursos compartidos.
* **Análisis Crítico:** Evaluar la eficiencia del mecanismo de sincronización utilizado frente a diferentes niveles de demanda y cómo afecta a la integridad de los datos.
* **Reflexión:** Desarrollar una comprensión práctica sobre los desafíos de implementar sincronización en sistemas operativos modernos.

## Modelo de Datos
La sala de cine está representada mediante una matriz de **10 filas por 15 columnas** (150 asientos en total).

### Estructura de Asiento (`Asiento` / `Seat`)
Cada asiento de la matriz almacena:
* `fila` (int): Coordenada de la fila en la sala.
* `columna` (int): Coordenada de la columna en la sala.
* `estaReservado` (bool) / `owner` (int): Estado que indica si el asiento está libre u ocupado. En caso de estar ocupado, puede almacenar el ID del usuario.

## Simulación de Concurrencia
1. **Inicialización:** La sala comienza con todos los asientos marcados como disponibles (no reservados).
2. **Usuarios (Hilos):** Los clientes se simulan a través de hilos (threads). Cada hilo cuenta con un identificador único (ID del Usuario).
3. **Solicitudes:** Cada hilo selecciona asientos (de forma aleatoria o predefinida) y lanza peticiones de reserva.
4. **Sección Crítica:** Antes de marcar un asiento como `Reservado`, el sistema verifica su disponibilidad. Este paso de verificación y escritura es atómico gracias a la protección mediante **semáforos o mutex**.

## Evaluación y Pruebas
El sistema permite realizar pruebas de estrés para evaluar:
* Comportamiento bajo altos niveles de concurrencia.
* Ausencia de bloqueos (*deadlocks*).
* Integridad y consistencia de los datos finales (sin asientos sobreescritos por dos usuarios a la vez).