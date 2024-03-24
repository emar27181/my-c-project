//完成版
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
  //最後尾に要素の追加
  table[count].id = save_string(id);
  table[count].info = info;

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
    tmp.id = save_string(table[i].id);
    tmp.info = table[i].info;

    //table[i - 1] とtable[i] のデータの交換
    table[i].id = save_string(table[i - 1].id);
    table[i].info = table[i - 1].info;
    table[i - 1].id = save_string(tmp.id);
    table[i - 1].info = tmp.info;

    i--; //デクリメント
  }

  count++; //要素数の加算

  //確認用出力
  check_table(count);
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

int main(void)
{
  char command[100], name[100];
  int year, t;

  //tableの初期化
  initialize_table();

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
