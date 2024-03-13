#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Definimos dos mutexes que representan los recursos compartidos
pthread_mutex_t recurso1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t recurso2 = PTHREAD_MUTEX_INITIALIZER;

// Función que simula el primer proceso, intenta adquirir recurso1 y luego recurso2
void* proceso1(void* arg) {
    while(1) { // Bucle infinito
        pthread_mutex_lock(&recurso1);
        printf("Proceso 1 ha adquirido recurso 1\n");
        sleep(1); // Espera para simular trabajo y aumentar la posibilidad de un deadlock
        printf("Proceso 1 intenta adquirir recurso 2\n");
        pthread_mutex_lock(&recurso2);
        printf("Proceso 1 ha adquirido recurso 2\n");
        // Simula el trabajo con los recursos
        sleep(1);
        // Libera los recursos
        pthread_mutex_unlock(&recurso2);
        pthread_mutex_unlock(&recurso1);
        sleep(1); // Espera antes de intentar adquirir los recursos nuevamente
    }
}

// Función que simula el segundo proceso, intenta adquirir recurso2 y luego recurso1
void* proceso2(void* arg) {
    while(1) { // Bucle infinito
        pthread_mutex_lock(&recurso2);
        printf("Proceso 2 ha adquirido recurso 2\n");
        sleep(1); // Espera para simular trabajo y aumentar la posibilidad de un deadlock
        printf("Proceso 2 intenta adquirir recurso 1\n");
        pthread_mutex_lock(&recurso1);
        printf("Proceso 2 ha adquirido recurso 1\n");
        // Simula el trabajo con los recursos
        sleep(1);
        // Libera los recursos
        pthread_mutex_unlock(&recurso1);
        pthread_mutex_unlock(&recurso2);
        sleep(1); // Espera antes de intentar adquirir los recursos nuevamente
    }
}

int main() {
    pthread_t hilo1, hilo2;
    // Crear los hilos (procesos)
    pthread_create(&hilo1, NULL, proceso1, NULL);
    pthread_create(&hilo2, NULL, proceso2, NULL);
    // Esperar a que los hilos terminen (en este caso, nunca terminan)
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    return 0;
}
