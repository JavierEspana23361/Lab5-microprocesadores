#include <stdio.h>
#include <omp.h>

int main(){
    int N = 10;
    int var1 = 0;
    int var2 = 1;
    #pragma omp parallel for shared(var1) private(var2)
    for(int i = 0; i < N; i++){
        var1 += 1;
        var2 += 1;
        printf("Thread %d: variable 1 = %d, variable 2 = %d\n", omp_get_thread_num(), var1, var2);
    }
    printf("variable 1 = %d, variable 2 = %d\n", var1, var2);
    return 0;
}