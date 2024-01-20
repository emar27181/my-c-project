#include <stdio.h>

int main()
{
  int n, i, j, a[100], in_num;

  for(i = 0; i < 100; i++)
    {
      a[i] = 0;
    }


  printf("n: ");
  scanf("%d", &n);

  for(i = 0; i < n; i++)
    {
      /*
      printf("input number\n");
      */
      scanf("%d", &in_num);
      a[i] = in_num;
    }

  i = 0;
  while(a[i] != 0)
    {
      printf("Divisors of %d are ", a[i]);
      for(j = 1; j <= a[i]; j++)
        {
          if(a[i] % j == 0)
            {
              printf("%d ", j);
            }
        }
      printf(".\n");

      i++;
    }

  return(0);

}
