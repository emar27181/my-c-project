#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARACTER 10000000
#define MAX_LINE 10000000

//buffer: 読み込まれた文字を保存する配列
//line: 各行の先頭の文字を指すポインタを保存する変数
//charCount: 読み込んだ文字数を保存する変数
//lineCount: 読み込んだ行数(単語数)を保存する変数
char buffer[MAX_CHARACTER];
char *line[MAX_LINE];
int charCount = 0, lineCount = 0;

int main(void){
    //lineHead: 種類ごとの先頭の文字のインデックスを保存する変数
    //count: ある単語が何回出現したかを数える変数
    int c = getchar(), lineHead = 0, count = 1;

    //最初の単語の例外的処理
    line[lineCount] = &buffer[charCount];
    lineCount++;

    //buffer, lineへの文字列の代入
    while(c != EOF){
        if(c == '\n' ){
            buffer[charCount] = '\0';
            charCount++;

            line[lineCount] = &buffer[charCount];
            lineCount++;
            c = getchar();
        }

        else{
            buffer[charCount] = c;
            charCount++;
            c = getchar();
        }
    }

    //countkind(ある種類の文字の個数)の計測
    for(int k = 0; k < lineCount - 1; k++)
    {

        //同じ文字が隣り合っている場合
        if(strcmp(line[k], line[k + 1]) == 0){
            count++;
        }

        //違う文字が隣り合っている場合
        else{
            printf("%d %s\n", count, line[lineHead]);
            lineHead += count;
            count = 1;
        }
    }

    return(0);
}