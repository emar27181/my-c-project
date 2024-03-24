#include <stdio.h>

int fact(int n)
{
    if(n != 0){
        return (n * fact(n - 1));
    }

    if(n == 0){
        return (1);
    }
}

int main(void)
{
    int n;

    scanf("%d", &n);

    printf(" fact(%d) = %d \n", n, fact(n));
    return (0);
}