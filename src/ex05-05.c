#include <stdio.h>
//N: 求めることのできるフィボナッチ数の最大のn
#define N 100

int fibonacci(int n)
{
    int fib[N];

    //定義通りに初期化
    fib[1] = 1;
    fib[2] = 1;

    for(int i = 3; i <= n; i++){
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    return(fib[n]);
}

int main(void)
{
    int n;
    scanf("%d", &n);
    printf("fibonacci(%d) = %d\n", n, fibonacci(n));
}