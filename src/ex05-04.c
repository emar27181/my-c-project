#include <stdio.h>

int fibonacci(int n);

int main (void){
    
    int n;

    scanf("%d", &n);

    printf("fibonacci(%d) = %d\n", n ,fibonacci(n));
}

int fibonacci(int n)
{
    if(n <= 2){
        return(1);
    }

    else if(n >= 3){
        return (fibonacci(n - 1) + fibonacci(n - 2));
    }
}
