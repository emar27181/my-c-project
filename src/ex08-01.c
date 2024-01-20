#include <stdio.h>
#include <stdlib.h>

int main(void){
    
    //c: 一文字ずつ文字を読み込む変数
    int c;

    //一文字目の代入
    c = getchar();

    while(c != EOF){
        if(('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')){
            putchar(c);
            c = getchar();
        }

        else{
            c = '\n';
            putchar(c);
            c = getchar();
        }

    }


    return (0);
}
