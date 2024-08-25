/*El programa original realiza lo siguiente:

Define un tamaño de arreglo N igual a 131072.
Inicializa un arreglo a de tamaño N con valores aleatorios.
Inserta manualmente el valor key en tres posiciones específicas del arreglo.
Cuenta cuántas veces aparece key en el arreglo utilizando la función count_key().
Imprime el número de apariciones de key.*/


/*Ejercicio 5 con los cambios respectivos*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 131072
#define THRESHOLD 1024  // Tamaño mínimo para el cual se crearán nuevas tareas

// Función recursiva que cuenta el número de apariciones de 'key' en un subarreglo
long parallel_count_key(long *a, long start, long end, long key) {
    long count = 0;

    if (end - start <= THRESHOLD) {
        // Si el tamaño del subarreglo es pequeño, contar secuencialmente
        for (long i = start; i < end; i++) {
            if (a[i] == key) count++;
        }
    } else {
        // Dividir el trabajo en dos mitades y crear tareas recursivamente
        long mid = start + (end - start) / 2;

        long count1 = 0, count2 = 0;

        #pragma omp task shared(count1)
        count1 = parallel_count_key(a, start, mid, key);

        #pragma omp task shared(count2)
        count2 = parallel_count_key(a, mid, end, key);

        #pragma omp taskwait  // Esperar a que las tareas terminen

        count = count1 + count2;
    }

    return count;
}

int main() {
    long a[N], key = 42, nkey = 0;

    // Inicialización del arreglo
    for (long i = 0; i < N; i++) a[i] = rand() % N;

    // Inserción manual de 'key' en tres posiciones específicas
    a[N % 43] = key; 
    a[N % 73] = key; 
    a[N % 3] = key;

    // Configurar el entorno OpenMP
    omp_set_num_threads(omp_get_max_threads());

    // Contar paralelamente
    #pragma omp parallel
    {
        #pragma omp single
        nkey = parallel_count_key(a, 0, N, key);
    }

    printf("Numero de veces que 'key' aparece paralelamente: %ld\n", nkey);

    return 0;
}
