#include <stdio.h>

int strlen1(const char *s)
{
    int count = 0;

    while(*s != NULL)
    {
        count++;
        s++;
    }

    return(count);
}

int main(void)
{
    char str1[] = "ABCDE";
    printf("str1 length = %d\n", strlen1(str1));

    return(0);
}