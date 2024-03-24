//線形リスト(先頭に挿入)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100000000
#define MAX_CHAR 10000000
#define MAX_WORD 1024

int char_top = 0;
char char_heap[MAX_CHAR];

struct cell
{
  char *id;
  int info;
  struct cell *next;
};
struct cell *head, *tail;

struct item
{
  char *id;
  int info;
};

struct item table[TABLE_SIZE];
int count;

int compare_item(const void *a, const void *b)
{
  return (strcmp(((struct item *)a)->id, ((struct item *)b)->id));
}

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
  count = 0;
}

void print_table(void)
{
  int i = 0;

  while (table[i].id != NULL)
  {
    printf("%d %s\n", table[i].info, table[i].id);
    i++;
  }
}

//リスト内のデータを先頭から順に出力する関数
void print_list(struct cell *head)
{
  struct cell *p = head;
  while (p != NULL)
  {
    table[count].id = p->id;
    table[count].info = p->info;
    count++;

    //printf("%d %s\n", p->info, p->id);
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

  //print_list(head);
  //printf("\n"); //改行
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
  int c, i;
  struct cell *p;
  char word[MAX_WORD + 1];

  initialize_table();
  c = getchar();
  while (c != EOF)
    if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
      c = getchar();

    else
    {
      i = 0;

      while ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
      {
        if (c >= 'A' && c <= 'Z')
          c += 'a' - 'A';

        if (i >= MAX_WORD)
        {
          printf("too long word\n");
          exit(1);
        }

        word[i] = c;
        i++;
        c = getchar();
      }
      word[i] = 0;
      p = search_table(word);
      if (p == NULL)
        insert_table(word, 1);
      else
        p->info++;
    }

  //tableのソート
  //qsort(table, count, sizeof(struct item), compare_item);

  print_list(head);

  qsort(table, count, sizeof(struct item), compare_item);
  print_table();
  return (0);
}
