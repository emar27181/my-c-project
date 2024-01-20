#include <stdio.h>

//再起関数permutationのプロトタイプ宣言
void permutation(int n, int k);

//perm[k]: k桁目の数字を保存する配列
//n: 表示する桁数とk桁目の最大の値
int perm[8];
int n;

int main(void)
{
    scanf("%d", &n);

    permutation(n, 0);

    return (0);
}

void permutation(int n, int k)
{
    //数字が全て用意されたので配列の内容を出力
    if (k == n){
        //数字の出力
        for(int i = 0; i < n; i++)
            printf("%d", perm[i]);
        printf("\n"); //改行
        return;
    }

    //k桁目の枠に1~nまでの数字を代入
    else{
        for(int i = 1; i <= n; i++){
            perm[k] = i;
            permutation(n, k + 1);
        }
    }
}