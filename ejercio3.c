#include <stdio.h>
#include <stdbool.h>

#define NUM_PROCESOS 5
#define NUM_RECURSOS 3

// Disponibles: Cantidad de recursos disponibles
int disponibles[NUM_RECURSOS] = {10, 5, 7};

// Máximo: Máxima demanda de cada proceso
int maximo[NUM_PROCESOS][NUM_RECURSOS] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

// Asignado: Cantidad de recursos asignados a cada proceso
int asignado[NUM_PROCESOS][NUM_RECURSOS] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

// Necesario: Cantidad de recursos que cada proceso aún necesita
int necesario[NUM_PROCESOS][NUM_RECURSOS];

// Calcula la matriz Necesario
void calcularNecesario() {
    for (int i = 0; i < NUM_PROCESOS; i++) {
        for (int j = 0; j < NUM_RECURSOS; j++) {
            necesario[i][j] = maximo[i][j] - asignado[i][j];
        }
    }
}

// Verifica si el proceso puede ejecutarse de manera segura
bool verificar(int proceso) {
    for (int i = 0; i < NUM_RECURSOS; i++) {
        if (necesario[proceso][i] > disponibles[i]) {
            return false;
        }
    }
    return true;
}

// Implementa el algoritmo del banquero
bool algoritmoDelBanquero() {
    calcularNecesario();
    bool finalizado[NUM_PROCESOS] = {false};
    int secuenciaSegura[NUM_PROCESOS];
    int contProcesosFinalizados = 0;

    while (contProcesosFinalizados < NUM_PROCESOS) {
        bool seguro = false;

        for (int i = 0; i < NUM_PROCESOS; i++) {
            if (!finalizado[i] && verificar(i)) {
                for (int j = 0; j < NUM_RECURSOS; j++) {
                    disponibles[j] += asignado[i][j];
                }
                secuenciaSegura[contProcesosFinalizados++] = i;
                finalizado[i] = true;
                seguro = true;
            }
        }

        if (!seguro) {
            printf("Los procesos están en un estado inseguro.\n");
            return false; // El sistema no está en un estado seguro
        }
    }

    printf("El sistema está en un estado seguro.\n");
    printf("Secuencia segura: ");
    for (int i = 0; i < NUM_PROCESOS; i++) {
        printf("%d ", secuenciaSegura[i]);
    }
    printf("\n");
    return true; // El sistema está en un estado seguro
}

int main() {
    algoritmoDelBanquero();
    return 0;
}
