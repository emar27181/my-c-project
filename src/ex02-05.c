#include <stdio.h>
#include <string.h>

int strcmp1(const char *str1, const char *str2)
{
  /*確認用出力*/
  //printf("*str1: %c(%d), *str2: %c(%d)\n", *str1, *str1, *str2, *str2);

  while(*str1 != NULL || *str2 != NULL)
    {
      /*文字数がstr1のほうが短い*/
      if(*str1 == NULL)
        return(-2);

      /*文字数がstr1のほうが長い*/
      if(*str2 == NULL)
        return(2);

      /*この時点では2つの配列は一致*/
      if(*str1 == *str2)
        {
          str1++;
          str2++;
          strcmp1(str1, str2);
        }

      /*str1の方が辞書順で前*/
      else if (*str1 < *str2)
        {
          return(-1);
        }

      /*str1の方が辞書順で後*/
      else if (*str1 > *str2)
        {
          return(1);
        }

    }

  /*2つの配列が完全に一致*/
  return(0);
}

int main(void) {
  char str1[] = "ABC";
  char str2[] = "ABC";

  printf("%d\n", strcmp1(str1, str2));

  return(0);

}
