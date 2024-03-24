#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  //f1: コピー元ファイルへのポインタ
  //f2: コピー先ファイルAへのポインタ
  //f3: コピー先ファイルBへのポインタ
  //c: 文字コードを保存していく変数
  FILE *f1, *f2, *f3;
  int c;

  //指定されたファイルをfに代入
  f1 = fopen("sample1.txt", "r");
  f2 = fopen("sample2.txt", "w");
  f3 = fopen("sample3.txt", "w");

  //ファイルの存在確認
  if (f1 == NULL) {
    fprintf(stderr, "sample1.txt cannot be opened\n");
    exit(1);
  }
  if (f2 == NULL) {
    fprintf(stderr, "sample2.txt cannot be opened\n");
    exit(1);
  }
  if (f3 == NULL) {
    fprintf(stderr, "sample3.txt cannnot be opened\n");
    exit(1);
  }

  //内容のコピー
  c = getc(f1);
  while (c != EOF) {
    //一文字ずつコピー
    putc(c, f2);
    putc(c, f3);
    c = getc(f1);
  }
  
  fclose(f1);
  fclose(f2);
  fclose(f3);

  return (0);
}