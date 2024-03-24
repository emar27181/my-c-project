#include <stdio.h>

char *strchr1(const char *s, int c)
{
  const char *p;

  for (p = s; *p != 0; p++)
    {
      if (*p == c)
        return ((char *)p);
    }
    
  return (NULL);
}

char *strchr2(const char s[], int c)
{
  int k;

  for (k = 0; s[k] != 0; k++)
    {
      if (s[k] == c)
	return ((char *)&s[k]);
    }
  return (NULL);
}

int main (void)
{
  char *p;
  char a[5];

  a[0] = 'a';
  a[1] = 'b';
  a[2] = 'c';
  a[3] = 'd';
  a[4] = 'e';

  /*確認用出力*/
  printf("a: %s\n", a);

  /*一回目のテスト*/
  printf("result1: ");
  p = strchr1(a, 'b');
  if(p != NULL)
    printf("%s\n", p);
  else 
    printf("not found\n");

  /*二回目のテスト*/
  printf("result2: ");
  p = strchr2(a, 'z');
  if(p != NULL)
    printf("%s\n", p);
  else 
    printf("not found\n");

  return(0);
}
