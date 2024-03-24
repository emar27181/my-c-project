//線形探索

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100000000
#define MAX_CHAR 100000000
#define MAX_WORD 1024

struct item
{
  char *id;
  int info;
};

struct item table[TABLE_SIZE];
int count;

int char_top = 0;
char char_heap[MAX_CHAR];

int compare_item(const void *a, const void *b)
{
  return (strcmp(((struct item *)a)->id, ((struct item *)b)->id));
}

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

//tableの内容を出力する関数
void check_table(int count)
{
  for (int t = 0; t < count; t++)
  {
    printf("table[%d].id = %s, table[%d].info = %d\n", t, table[t].id, t, table[t].info);
  }

  printf("count = %d\n", count);
}

void insert_table(char *id, int info)
{

  //要素数が0の場合
  /*if (count == 0)
    {
      //要素の追加
      table[count].id = save_string(id);
      table[count].info = 1;

      count++; //要素数の加算

      //確認用出力
      // check_table(count);
    }

  //要素数が1以上の場合
  else
    {*/
  //確認用出力
  //printf("search_table(%s) = %d\n", id, search_table(id));

  //すでに登録されている文字が入力された場合
  if (search_table(id) != -1)
  {
    table[search_table(id)].info++;
  }

  //まだ登録されていない文字が入力された場合
  else
  {
    //最後尾に要素の追加
    table[count].id = save_string(id);
    table[count].info++;

    count++; //要素数の加算

    //確認用出力
    //check_table(count);
  }
  //}
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

void print_table(void)
{
  int i = 0;

  while (table[i].id != NULL)
  {
    printf("%d %s\n", table[i].info, table[i].id);
    i++;
  }
}

int main(void)
{
  int c, i, p;
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
      if (p == -1)
        insert_table(word, 1);
      else
        table[p].info++;
    }

  //*tableのソート
  qsort(table, count, sizeof(struct item), compare_item);

  print_table();
  return (0);
}
