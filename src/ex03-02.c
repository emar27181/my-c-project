#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{ 
  //f1: コピー元ファイルへのポインタ
  //f2: コピー先ファイルへのポインタ
  //c: 文字コードを保存していく変数
  FILE *f1, *f2;
  int c;

  //コマンド引数の個数の正常性の確認
  if (argc != 3) {
    fprintf(stderr, "number of command arguments should be changed\n");
    exit(1);
  }

  //コマンドで指定されたファイルをfに代入
  f1 = fopen(argv[1], "r");
  f2 = fopen(argv[2], "w");

  //ファイルの存在確認
  if (f1 == NULL) {
    fprintf(stderr, "%s cannot be opened\n", argv[1]);
    exit(1);
  }
  if (f2 == NULL) {
    fprintf(stderr, "%s cannot be opened\n", argv[2]);
    exit(1);
  }

  //内容のコピー
  c = getc(f1);
  while (c != EOF) {
    //一文字ずつコピー
    putc(c, f2);
    c = getc(f1);
  }
  
  fclose(f1);
  fclose(f2);

  return (0);
}