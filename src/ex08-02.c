#include <stdio.h>
#include <stdlib.h>

int main(void){

    int c, cKeep; 
    
    //cに1文字目を代入
    c = getchar();

    putchar(c);

    //cKeepにcの値を保持
    cKeep = c;

    //c次の文字を代入
    c = getchar();

    while(c != EOF){

        //空行の場合
        if(cKeep == '\n' && c == '\n'){
            cKeep = c;
            c = getchar();
        }

        //空行以外の場合
        else{
            putchar(c);
            cKeep = c;
            c = getchar();
        }
    }

    return (0);
}