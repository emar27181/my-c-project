#include <stdio.h>
#include <stdlib.h>
//N: 保存する配列の最大個数(=読み取れる数値の最大個数)
#define N 100

int main(void)
{
    
    FILE *f;
    //num: ファイル内の数字の個数を保存する変数
    //check: 保存できた個数を保存する変数

    int i, num = 0, check = 0,  a[N], sum = 0;

    //配列aの初期化
    for(i = 0; i < N; i++){
        a[i] = 0;
    }
    
    //ファイルの展開
    f = fopen("integers.txt", "r");

    //エラー出力
    if(f == NULL){
        fprintf(stderr, "integers.txt cannnot be opened\n");
        exit(1);
    }

    i = 0;
    while(fscanf(f, "%d", &a[i]) != EOF){

        //確認用出力
        /*
        printf("a[%d] = %d\n", i, a[i]);
        */

        //インデックスの進行
        i++;
    }

    //numに要素の個数を代入
    num = i;

    //配列の出力(確認用出力)
    for(i = 0; i < num; i++){
        printf("%8d\n", a[i]);
    }

    //和の計算
    for(i = 0; i < num; i++){
        sum += a[i];
    }

    printf("n = %d\n", num);
    printf("sum = %d\n", sum);

    return(0);
}