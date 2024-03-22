#include <stdio.h>

int a[100];

int main()
{
  int i, v;

  for (i = 0; i < 100; i++)
    a[i] = i;

  v = f(100000);
  printf("%d\n", v);

  return (0);
}

int f(int n)
{
  int i, s;

  s = 0;
  i = 1;
  while (i < n) {
    s = s + a[i];
    i = 2 * i;
  }

  return (s);
}
