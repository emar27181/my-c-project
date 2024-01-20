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

int compare_line(const void * a, const void * b);

int main(void){

    //c: 文字を読み込む変数(次の文字を読み込んでcKeepとの比較も行う)
    //cKeep: cの文字コードを保持する変数
    int c = getchar();
    int cKeep = c;
    

    line[lineCount] = &buffer[charCount];
    lineCount++;

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

    //第2引数の行数の定義が曖昧???
    qsort(line, lineCount - 1, sizeof(char *), compare_line);

    //for文の始めを0にすると謎の空行が出力されてしまう???
    for(int i = 0; i < lineCount - 1; i++){
        printf("%s\n", line[i]);
    }
}

int compare_line(const void * a, const void * b){
    return (strcmp(*(char **)a, *(char **)b));
}

