#include <stdio.h>
#include <stdlib.h>
//N: 保存する配列の最大個数(=読み取れる数値の最大個数)
#define N 100

int main(int argc, char *argv[])
{
    
    FILE *f;

    //a: 入力値1
    //b: 入力値2
    //r: fscanfによって代入できた変数の個数を保存する変数
    int a, b, r;
    
    //ファイルの展開
    f = fopen(argv[1], "r");

    //エラー出力
    if(f == NULL){
        fprintf(stderr, "%s cannnot be opened\n", argv[1]);
        exit(1);
    }

    while((r = fscanf(f, "%d,%d", &a, &b)) != EOF){

        printf("num of success: %d\n", r);
        
        //2つの値が正しく代入できた場合
        if(r == 2){
            printf("a = %d, b = %d, a + b = %d\n", a, b, a + b);
        }

        //2つの値が正しく代入できなかった場合
        else{
            printf("error\n");
            break;
        }

        //改行
        printf("\n");

    }
    
    fclose(f);
    return(0);
}

//テストファイル
/*
22,44
222, 

   444
212,432      
   323 22
*/