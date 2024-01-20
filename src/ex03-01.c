#include <stdio.h>
#include <stdlib.h>

int main(void)
{ 
  //f: ファイルへのポインタ
  //c: 
  //count: 文字数(=ファイルの大きさ)を数える変数
  FILE *f;
  int c, count = 0;

  //コマンドで指定されたファイルをfに代入
  f = fopen("sample.txt", "r");

  //ファイルの存在確認
  if (f == NULL) {
    fprintf(stderr, "sample.txt cannot be opened\n");
    exit(1);
  }

  //ファイルの大きさの計測
  //cに最初の文字を代入
  c = getc(f);

  while (c != EOF) {
    c = getc(f);
    count++;
  }
  fclose(f);
  
  //ファイルの大きさの出力
  printf("sample.txt is %d bite.\n", count);

  return (0);
}