#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    //f1: 比較ファイルA
    //f2: 比較ファイルB
    FILE *f1, *f2;
    //c1: ファイルAの文字を保存する変数
    //c2: ファイルBの文字を保存する変数
    //count: 何文字文探索したかを保存する変数
    int c1, c2, count;

    //コマンドで指定されたファイルをf1, f2に代入
    f1 = fopen(argv[1], "r");
    f2 = fopen(argv[2], "r");

    //ファイルの存在確認
    if (f1 == NULL) {
        fprintf(stderr, "%s cannot be opened\n", argv[1]);
        exit(1);
    }
    if (f2 == NULL) {
        fprintf(stderr, "%s cannot be opened\n", argv[2]);
        exit(1);
    }

    //c1, c2に最初の文字を代入
    c1 = getc(f1);
    c2 = getc(f2);
    
    //countの初期化
    count = 0;

    while(c1 != EOF || c2 != EOF)
    {
        //探索済みの容量(byte)の更新
        count++;

        //比較ファイルAの方が短い場合
        if(c1 == EOF){
            printf("%s is shorter than %s(%d byte)\n", argv[1], argv[2], count - 1);
            exit(1);
        }

        //比較ファイルBの方が短い場合
        if(c2 == EOF){
            printf("%s is shorter than %s(%d byte)\n", argv[2], argv[1], count - 1);
            exit(1);
        }

        //
        if(c1 != c2){
            printf("wrong(%2d byte) -> %c(A), %c(B)\n", count, c1, c2);
            exit(1);
        }

        //次の文字をそれぞれ代入
        c1 = getc(f1);
        c2 = getc(f2);

    }

    //全く同じコード?
    printf("%s and %s is same\n", argv[1], argv[2]);

    return(0);
}