#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 257
//#define M 2
#define MAX_CHAR 10000

struct item
{
  char *id;
  int info;
};
struct item table[M];
int mark[M];

int char_top = 0;
char char_heap[MAX_CHAR];

char *save_string(char *s)
{
  int result;

  result = char_top;
  for (;;)
  {
    if (char_top >= MAX_CHAR)
    {
      printf("string buffer overflow\n");
      exit(1);
    }
    char_heap[char_top] = *s;
    char_top++;
    if (*s == 0)
      break;
    s++;
  }
  return (&char_heap[result]);
}

int hash(char *v)
{
  int x;
  x = 0;
  while (*v != 0)
    x = 256 * x + (*v++);
  x = x % M;
  if (x < 0)
    x = (-x);
  return (x);
  //return(0);
}

void initialize_table(void)
{
  int i;
  for (i = 0; i < M; i++)
    mark[i] = 0;
}

void insert_table(char *id, int info)
{
  //x: 検索しているハッシュ値を保存している変数
  //ep: 始めのハッシュ値
  int x, ep;
  x = hash(id);
  ep = x;

  //table[x]にデータがある場合
  while (mark[x] == 1)
  {
    //keyが見つかった場合(二重登録)
    if (strcmp(table[x].id, id) == 0)
    {
      printf("%sはすでに登録されています.\n", id);
      return;
    }

    //keyが見つからなかった場合
    x = (x + 1) % M; //xの更新

    //エラー出力
    if (x == ep)
    {
      printf("最大個数を超えました\n");
      return;
    }
  }

  //table[x]にデータがない場合
  table[x].id = save_string(id);
  table[x].info = info;
  mark[x] = 1;
  printf("table[%d].id = %s, table[%d].info = %d\n", x, table[x].id, x, table[x].info);
}

int search_table(char *id)
{
  //x: 検索しているハッシュ値を保存している変数
  //ep: 始めのハッシュ値
  int x, ep;
  x = hash(id);
  ep = x;

  //table[x]にデータがある場合
  while (mark[x] == 1)
  {
    //keyが見つかった場合
    if (strcmp(table[x].id, id) == 0)
      return (x); //ハッシュ値の返し

    //keyが見つからなかった場合
    x = (x + 1) % M; //xの更新
    //ハッシュ値の衝突???
    if (x == ep)
      return (-1); //
  }

  //table[x]にデータがない場合
  return (-1);
}

int main(void)
{
  char command[100], name[100];
  int year, t;

  //i: 探索又は追加した回数を保存する変数
  int i = 0;

  for (;; i++)
  {
    char a = scanf("%s %s", command, name);

    //読み込みを終了する場合
    if (a == EOF)
    {
      //9.3.3
      printf("終了(EOFが入力されました)\n");
      break;
    }

    //要素の探索を実行する場合
    if (command[0] == 'S')
    {
      //対象の要素が存在しない場合
      if (search_table(name) == -1)
      {
        printf("%sは登録されていません\n\n", name);
      }

      //対象の要素が存在する場合
      else
      {
        printf("%sは%d年生まれです\n\n", name, table[search_table(name)].info);
      }
    }

    //要素の追加を実行する場合
    else if (command[0] == 'I')
    {
      //対象の要素が存在する場合
      if (search_table(name) != -1)
      {
        printf("すでに%sは登録されています\n\n", name);
      }

      //対象の要素が存在しない場合
      else
      {
        printf("%sの生年を入力してください\n", name);
        scanf("%d", &year);
        insert_table(name, year);
        printf("\n"); //改行
      }
    }

    //エラー出力
    else
    {
      printf("commandが正しく入力されていません\n");
    }
  }

  return (0);
}
