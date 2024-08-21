#include <stdio.h>
#include <omp.h>

int main(){
    int N = 999999999;
    double start_time, run_time;
    int i, sum = 0;
    start_time = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum)
    for(i = 1; i <= N; i++){
        sum += i;
    }
    run_time = omp_get_wtime() - start_time;
    printf("La suma de los primeros %d numeros naturales es: %d\n", N, sum);
    printf("Tiempo de ejecucion: %f\n", run_time);
    return 0;
}