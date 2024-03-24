#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 1000000
#define MAX_CHAR 10000000

struct item
{
  char *id;
  int info;
};

struct item table[TABLE_SIZE];
int count;

int char_top = 0;
char char_heap[MAX_CHAR];

char *save_string(char *s) /* 文字列を配列 char_heap に保存する */
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

void initialize_table(void)
{
  count = 0;
}

//9.3.1
void insert_table(char *id, int info)
{

  //過剰代入のエラー出力
  if (count > TABLE_SIZE)
  {
    printf("代入個数がtableの最大個数を超過しています\n");
    exit(1);
  }

  //table[count]の要素の追加
  table[count].id = save_string(id); //※save_stringにとるidの保持しながらアドレスの代入
  table[count].info = info;

  //要素数の加算
  count++;

  //9.3.2
  //確認用出力
  for (int t = 0; t < count; t++)
  {
    printf("table[%d].id = %s, table[%d].info = %d\n", t, table[t].id, t, table[t].info);
  }
}

//帰属判定をする関数
int search_table(char *id)
{
  int i;

  for (i = 0; i < count; i++)
    if (strcmp(id, table[i].id) == 0)
      return (i);
  return (-1);
}

int main(void)
{
  char command[100], name[100];
  int year, t;

  //tableの初期化
  initialize_table();

  //tableへ要素の代入
  /*
  insert_table("Copernicus", 1473);
  insert_table("Galilei", 1564);
  insert_table("Newton", 1643);
  insert_table("Maxwell", 1831);
  insert_table("Einstein", 1879);
  insert_table("Heisenberg", 1901);

  printf("\n"); //改行

  //"Newton"の探索
  t = search_table("Newton");
  if (t == -1)
    printf("not found.\n");
  else
    printf("%d\n", table[t].info);
  */
  //i: 探索又は追加した回数を保存する変数
  int i = 0;

  for (;; i++)
  {
    char a = scanf("%s %s", command, name);

    //確認用出力
    //printf("i = %d: ", i);

    //読み込みを終了する場合
    if (a == EOF)
    {
      //9.3.3
      printf("終了(EOFが入力されました)\n"); //終了???
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

    //確認用出力
    /*
    for(int k = 0; k < 10; k++){
      printf("command[%d] = %c, name[%d] = %c\n", k, command[k], k, name[k]);
    }
    */
  }

  return (0);
}
