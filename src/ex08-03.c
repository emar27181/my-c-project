#include <stdio.h>
#include <stdlib.h>

int main(void){
    int c;

    c = getchar();

    while(c != EOF){
        if(('A' <= c && c <= 'Z')){
            c = c + ('a' - 'A');
            putchar(c);
            c = getchar();
        }

        else{
            putchar(c);
            c = getchar();
        }
    }
}