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

        while(p != NULL)
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
}

int main(void)
{
    struct cell *p;
    int h = hHead;

    initialize_table(); //tableの初期化

    int c, i;
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

    copy_table();

    print_tableCopy(); //確認用出力

    //printf("count_strcmp = %lld\n", count_strcmp); //確認用出力

    return (0);
}
