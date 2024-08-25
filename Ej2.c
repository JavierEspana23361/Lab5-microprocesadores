#include <stdio.h>
#include <omp.h>

int main(){
    int N = 999999999; //Defino el número hasta el cual se sumarán los números naturales
    double start_time, run_time;
    int i, sum = 0;
    start_time = omp_get_wtime(); //Inicio el contador de tiempo


    #pragma omp parallel for reduction(+:sum) //Paralelizo el for y hago la reducción de la suma
    for(i = 1; i <= N; i++){
        sum += i;
    }

    run_time = omp_get_wtime() - start_time; //Calculo el tiempo de ejecución
     
    printf("La suma de los primeros %d numeros naturales es: %d\n", N, sum); //Imprimo la suma
    printf("Tiempo de ejecucion: %f\n", run_time); //Imprimo el tiempo de ejecución
    return 0;
}