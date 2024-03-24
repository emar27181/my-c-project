//線形リスト

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

    //ソートの探索対象のインデックスを保存するデクリメント
    int i = count;

    //tableのソート
    //*while文の条件文は左から実行されるため、先にtableの範囲外参照を抑える条件(i >= 1)を記述
    //*しないと、table[-1]という存在しない対象を参照してしまいSegmentation faultが起きる
    while (i >= 1 && strcmp(table[i - 1].id, table[i].id) > 0)
    {

      //tmp: 一時的に値を保持する変数
      struct item tmp;

      //tmpにiのデータを保持
      tmp.id = table[i].id;
      tmp.info = table[i].info;

      //table[i - 1] とtable[i] のデータの交換
      table[i].id = table[i - 1].id;
      table[i].info = table[i - 1].info;
      table[i - 1].id = tmp.id;
      table[i - 1].info = tmp.info;

      i--; //デクリメント
    }

    count++; //要素数の加算

    //確認用出力
    //check_table(count);
  }
}

//二分探索によって帰属判定をする関数
int search_table(char *id)
{
  int lo, hi, mid;
  lo = 0;
  hi = count - 1;
  while (lo <= hi)
  {
    mid = (lo + hi) / 2;
    if (strcmp(id, table[mid].id) < 0)
      hi = mid - 1;
    else
      lo = mid + 1;
  }
  if (hi >= 0 && strcmp(id, table[hi].id) == 0)
    return (hi);
  else
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
  print_table();
  return (0);
}
