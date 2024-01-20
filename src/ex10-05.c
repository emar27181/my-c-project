//自己再生リスト(先頭に挿入)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 10000000

int char_top = 0;
char char_heap[MAX_CHAR];

struct cell
{
  char *id;
  int info;
  struct cell *next;
};
struct cell *head;

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

void initialize_table(void)
{
  head = NULL;
}

//リスト内のデータを先頭から順に出力する関数
void print_list(struct cell *head)
{
  struct cell *p = head;
  while (p != NULL)
  {
    printf("id = %s, info = %d\n", p->id, p->info);
    p = p->next;
  }
}

struct cell *new_cell(void)
{
  struct cell *p; //cell型のpを宣言

  p = (struct cell *)malloc(sizeof(struct cell)); //pのメモリを確保

  //エラー出力
  if (p == NULL)
  {
    printf("memory allocation failed\n");
    exit(1);
  }

  return (p);
}

void insert_table(char *id, int info)
{
  struct cell *p = new_cell();

  p->id = save_string(id);
  p->info = info;
  p->next = head;
  head = p;

  print_list(head);
  printf("\n"); //改行
}

struct cell *search_table(char *id)
{
  //p: 探索しているアドレスを保存しているポインタ
  //pKeep: pの指すアドレスの１つ前のアドレスを指すポインタ
  struct cell *p, *pKeep;

  p = head; //pの指すアドレスを先頭に設定
  //idの探索
  while (p != NULL)
  {
    //idが見つかった場合
    if (strcmp(id, p->id) == 0)
    {
      //先頭の要素が検索対象(id)だった場合
      if (strcmp(id, head->id) == 0)
      {
        printf("検索対象(%s)はすでに先頭に存在します\n", id);
        print_list(head);
        printf("\n"); //改行
        return (p);
      }

      else
      {
        pKeep->next = p->next; //pの一つ前のセルのnextをp->nextに設定
        p->next = head;        //pのnextを先頭に設定
        head = p;              //見つかったセルをheadに代入し、headの更新

        printf("検索対象(%s)が先頭に挿入されました\n", id);
        print_list(head);
        printf("\n"); //改行

        return (p);
      }
    }
    pKeep = p;
    p = p->next; //pに次のアドレスを代入
  }

  return (NULL);
}

int main(void)
{
  struct cell *p;

  initialize_table(); //tableの初期化

  insert_table("Copernicus", 1473);
  insert_table("Galilei", 1564);
  insert_table("Newton", 1643);
  insert_table("Maxwell", 1831);
  insert_table("Einstein", 1879);
  insert_table("Heisenberg", 1901);

  p = search_table("Newton");
  if (p == NULL)
    printf("not found.\n");
  else
    printf("%d\n", p->info);

  p = search_table("Maxwell");
  if (p == NULL)
    printf("not found.\n");
  else
    printf("%d\n", p->info);

  p = search_table("Maxwell");
  if (p == NULL)
    printf("not found.\n");
  else
    printf("%d\n", p->info);

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
      if (search_table(name) == NULL)
      {
        printf("%sは登録されていません\n\n", name);
      }

      //対象の要素が存在する場合
      else
      {
        printf("%sは%d年生まれです\n\n", name, search_table(name)->info);
      }
    }

    //要素の追加を実行する場合
    else if (command[0] == 'I')
    {
      //対象の要素が存在する場合
      if (search_table(name) != NULL)
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
