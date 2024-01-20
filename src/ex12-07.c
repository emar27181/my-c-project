#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 50000
#define TABLE_SIZE 50000
#define MAX_CHAR 10000000
#define MAX_WORD 1024

struct cell
{
    char *id;
    int info;
    struct cell *next;
};
struct cell *hashtable[M];

//tableCopy[M]: (hash?)tableの中身を左詰めでコピーする配列
struct cell tableCopy[TABLE_SIZE];
int count;

struct cell table[TABLE_SIZE];
int next_cell;

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
}

void initialize_table(void)
{
    int i;
    for (i = 0; i < M; i++)
        hashtable[i] = NULL;
    next_cell = 0;
}

struct cell *new_cell(void)
{
    struct cell *p;
    p = (struct cell *)malloc(sizeof(struct cell));
    if (p == NULL)
    {
        printf("memory allocation failed\n");
        exit(1);
    }
    return (p);
}

void print_list(struct cell *h)
{
    struct cell *p;
    p = h;
    while (p != NULL)
    {
        printf("%d %s\n", p->info, p->id);
        p = p->next;
    }
}

//hHead: hashtableの先頭のインデックス
int hHead;

void insert_table(char *id, int info)
{
    struct cell *p = new_cell();
    int h;

    p->id = save_string(id);
    p->info = info;
    h = hash(id);
    p->next = hashtable[h];
    hashtable[h] = p;
    hHead = h;

    //print_list(hashtable[h]); //確認用出力(ハッシュ値の衝突)
    //printf("\n"); //改行
}

long long int count_strcmp = 0;

struct cell *search_table(char *id)
{
    int h;
    struct cell *p;

    h = hash(id);
    p = hashtable[h];

    while (p != NULL)
    {
        count_strcmp++;
        if (strcmp(id, p->id) == 0)
        {
            return (p);
        }
        p = p->next;
    }
    return (NULL);
}

int compare_item(const void *a, const void *b)
{
    return (strcmp(((struct cell *)a)->id, ((struct cell *)b)->id));
}

void copy_table(void)
{
    int k = 0;
    for (int i = 0; i < M; i++)
    {
        struct cell *p = hashtable[i];

        while (p != NULL)
        {
            tableCopy[k].id = p->id;
            tableCopy[k].info = p->info;
            k++;
            p = p->next;
        }
    }

    count = k;

    qsort(tableCopy, count, sizeof(struct cell), compare_item);
}

void print_tableCopy(void)
{
    for (int i = 0; i < count; i++)
    {
        //printf("tableCopy[%d].id = %s, tableCopy[%d].info = %d\n", i, tableCopy[i].id, i, tableCopy[i].info);
        printf("%d %s\n", tableCopy[i].info, tableCopy[i].id);
    }
}

void delete_table(char *id)
{
    int h = hash(id);
    struct cell *p = hashtable[h];
    struct cell *pKeep;

    if (strcmp(p->id, id) == 0)
    {
        hashtable[hash(id)] = p->next;
        return;
    }

    while (p->next != NULL)
    {
        //idが見つかった場合
        if (strcmp(p->next->id, id) == 0)
        {
            //検索対象が先頭以外で見つかった場合
            pKeep = p->next;
            pKeep->next = p->next;
            break;
        }
        p = p->next;
    }
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
        printf("command = %s, name = %s\n", command, name);

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

        //要素の削除を実行する場合
        else if (command[0] == 'D')
        {
            //対象の要素が存在する場合
            if (search_table(name) != NULL)
            {
                delete_table(name);
                printf("%sは削除されました\n\n", name);
            }

            //対象の要素が存在しない場合
            else
            {
                printf("%sは存在しません\n\n", name);
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
