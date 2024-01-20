#include <stdio.h>

char *strcat1(char *dest, const char *src)
{
    char *start;
    start = dest;

    while(*dest != NULL)
    {
        dest++;
    }

    
    while(*src != NULL)
    {
        *dest = *src;
        dest++;
        src++;
    }

    return (start);
}

int main(void)
{
    char first[20] = "abc";
    printf("result = %s\n", strcat1(first, "def"));

    return(0);
}