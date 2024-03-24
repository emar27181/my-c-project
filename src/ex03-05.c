#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    FILE *f;
    //count: インデックスに対応する文字の個数を保存する配列
    //c: 文字を保存していく変数
    int i, c, count[256];

    //配列countの初期化
    for(i = 0; i < 256; i++)
    {
        count[i] = 0;
    }

    //ファイルの展開
    f = fopen(argv[1], "r");

    //エラー出力
    if(f == NULL)
    {
        fprintf(stderr, "%s cannot be opened\n", argv[1]);
        exit(1);
    }

    //cへの代入と出力
    c = getc(f);
    while(c != EOF)
    {   
        //cに対応するインデックスの配列の値を1加算
        count[c]++;
        c = getc(f);
    }

    for(i = 0; i < 256; i++)
    {
        if(i >= 32 && i <= 126)
            printf("%c(%3d): %2d \n", i, i, count[i]);
    }
    

    return(0);
}