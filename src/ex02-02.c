#include <stdio.h>

char *strcpy1(char *dest, const char *src)
{
    char *start;
    start = dest;

    while(*src != NULL)
    {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0';
    dest++;
    
    return (start);
}

int main(void)
{
    char str1[] = "ABC";
    char str2[10];

    strcpy1(str2, str1);

    printf("str1 = %s\n", str1);
    printf("str2 = %s\n", str2);
}