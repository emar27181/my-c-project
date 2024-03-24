#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]){
    FILE *f;
    int c, i;

    for(i = 1; i < argc; i++)
    {
        //ファイルの展開
        f = fopen(argv[i], "r");
        
        //エラー出力
        if(f == NULL)
        {
            fprintf(stderr, "%s cannot be opened\n", argv[i]);
            exit(1);
        }

        //cへの文字の代入と出力
        c = getc(f);
        while (c != EOF)
        {
            putchar(c);
            c = getc(f);
        }

        //ファイルの縮小
        fclose(f);

    }

    return(0);
}