#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_FILOSOFOS 5

// Semáforos para los tenedores.
sem_t tenedores[NUM_FILOSOFOS];

// Semáforo para controlar el acceso al recurso de los tenedores.
sem_t control;

void* filosofo(void* num) {
    int* i = num;

    while(1) {
        printf("Filósofo %d está pensando.\n", *i);
        sleep(1);

        sem_wait(&control); // Intenta entrar a la sección de control

        sem_wait(&tenedores[*i]); // Intenta tomar el tenedor a su izquierda
        sem_wait(&tenedores[(*i + 1) % NUM_FILOSOFOS]); // Intenta tomar el tenedor a su derecha

        sem_post(&control); // Sale de la sección de control

        printf("Filósofo %d está comiendo.\n", *i);
        sleep(1);

        sem_post(&tenedores[*i]); // Libera el tenedor de su izquierda
        sem_post(&tenedores[(*i + 1) % NUM_FILOSOFOS]); // Libera el tenedor de su derecha
    }

    pthread_exit(NULL);
}

int main() {
    int i;
    int filosofos[NUM_FILOSOFOS];
    pthread_t thread[NUM_FILOSOFOS];

    // Inicializa los semáforos para los tenedores
    for (i = 0; i < NUM_FILOSOFOS; i++) {
        sem_init(&tenedores[i], 0, 1);
    }

    // Inicializa el semáforo de control
    sem_init(&control, 0, NUM_FILOSOFOS - 1);

    // Crea un hilo por filósofo
    for (i = 0; i < NUM_FILOSOFOS; i++) {
        filosofos[i] = i;
        pthread_create(&thread[i], NULL, filosofo, &filosofos[i]);
    }

    // Espera que los hilos terminen (nunca terminarán en este ejemplo)
    for (i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_join(thread[i], NULL);
    }

    // Limpieza (nunca se alcanzará en este ejemplo, pero es una buena práctica)
    for (i = 0; i < NUM_FILOSOFOS; i++) {
        sem_destroy(&tenedores[i]);
    }
    sem_destroy(&control);

    return 0;
}
