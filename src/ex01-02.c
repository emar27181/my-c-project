#include <stdio.h>
#define N 100

int main()
{
  int i, j, n, k, a[N], a_keep;

  /*配列の初期化*/
  for(i = 0; i < N; i++)
    {
      a[i] = 0;
    }

  /*値の入力*/
  printf("n: ");
  scanf("%d", &n);

  printf("k: ");
  scanf("%d", &k);

  /*ソートを大きい順にしてしまったための辻褄合わせ*/
  k = n - k;

  for(i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
    }

  /*確認用出力*/
  /*
  for(i = 0; i < n; i++)
    {
      printf("a[%d]: %d\n", i, a[i]);
    }
  printf("\n");
  */
  
  /*配列の中身を大きい順にソート*/
  for(j = 0; j < 100; j++)
    {
      i = 0;
      while(a[i] != 0)
	{
	  if(a[i] < a[i + 1])
	    {
	      a_keep = a[i];
	      a[i] = a[i + 1];
	      a[i + 1] = a_keep;

	      /*確認用出力*/
	      /*
	      printf("a[%d]: %d, a[%d]: %d\n", i, a[i], i + 1, a[i + 1]);
	      */
	    }
	  i++;
	}
    }


  /*確認用出力*/
  /*
  printf("\n");
  for(i = 0; i < n; i++)
    {
      printf("a[%d]: %d\n", i, a[i]);
    }
  */

  /*結果の出力*/
  if(a[k] != a[k + 1])
    {
      printf("\n%d\n", a[k]);
    }
  
  else
    {
      printf("No such value\n");
    }

  return(0);
  
}
      
  
