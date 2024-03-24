#include <stdio.h>

int nAry(int x, int b);

int main (void){

    //x: 変換される整数値(x >= 0)
    //b: xを何進数で表現するかを保存する変数(2 <= b <= 10)

    int x, b;

    scanf("%d %d", &x, &b);

    nAry(x, b);

    printf("\n");
}

int nAry(int x, int b){
    
    if(x < b){
        printf("%d", x);
    }

    else{
        nAry(x / b, b);
        printf("%d", x % b);
    }
}