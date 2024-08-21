#include <stdio.h>  
#include <omp.h>

int factorial(int n){
    int fact = 1;
    for(int i = 1; i <= n; i++){
        fact *= i;
    }
    return fact;
}

int fibonacci(int n){
    if(n == 0){
        return 0;
    }
    if(n == 1){
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int max(int arr[], int n){
    int max = arr[0];
    for(int i = 1; i < n; i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }
    return max;
}

int main(){
    int N = 10;
    int arr[N];
    for(int i = 0; i < N; i++){
        arr[i] = i;
    }
    int fact, fib, max_val;
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            fact = factorial(N);
            printf("Factorial de %d: %d\n", N, fact);
        }
        #pragma omp section
        {
            fib = fibonacci(N);
            printf("Fibonacci de %d: %d\n", N, fib);
        }
        #pragma omp section
        {
            max_val = max(arr, N);
            printf("Maximo en el arreglo: %d\n", max_val);
        }
    }
    return 0;
}