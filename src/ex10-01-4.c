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
struct cell *head, *tail;

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
  tail = NULL;
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
  struct cell *p = new_cell(); //pのメモリの確保

  //pへ情報の代入
  p->id = save_string(id); 
  p->info = info;

  p->next = NULL; //最後尾に追加なので、nextにはNULLを代入

  //要素数が0のとき
  if (head == NULL && tail == NULL)
  {
    head = p; //先頭を指すheadの更新
    tail = p; //最後尾を指すtailの更新
  }

  //要素数が1以上のとき
  else
  {
    tail->next = p; //今までの最後尾のnextを新しく作成したセルに設定
    tail = p; //最後尾を指すtailの更新
  }

  print_list(head);
  printf("\n"); //改行
}

struct cell *search_table(char *id)
{
  struct cell *p;

  p = head;
  while (p != NULL)
  {
    if (strcmp(id, p->id) == 0)
      return (p);
    p = p->next;
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
