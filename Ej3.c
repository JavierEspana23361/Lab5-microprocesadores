#include <stdio.h>  
#include <omp.h>

// Función que calcula el factorial de un número
int factorial(int n){
    int fact = 1;
    for(int i = 1; i <= n; i++){
        fact *= i;
    }
    return fact;
}

// Función que calcula el n-ésimo número de Fibonacci
int fibonacci(int n){
    if(n == 0){
        return 0;
    }
    if(n == 1){
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Función que calcula el máximo de un arreglo
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
    for(int i = 0; i < N; i++){ //Inicializo el arreglo, con valores de 0 a N-1
        arr[i] = i;
    }
    int fact, fib, max_val;
    #pragma omp parallel sections //Divido el trabajo en secciones
    {
        #pragma omp section //Primera sección
        {
            fact = factorial(N); //Calculo el factorial de N
            printf("Factorial de %d: %d\n", N, fact);
        }
        #pragma omp section //Segunda sección
        {
            fib = fibonacci(N); //Calculo el fibonacci de N
            printf("Fibonacci de %d: %d\n", N, fib);
        }
        #pragma omp section //Tercera sección
        {
            max_val = max(arr, N); //Calculo el máximo del arreglo
            printf("Maximo en el arreglo: %d\n", max_val);
        }
    }
    return 0;
}