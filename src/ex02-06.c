#include <stdio.h>

char *strstr1(const char *s1, const char *s2)
{
  /*Save1: s1のポインタを保存*/
  /*Save2: s2のポインタを保存*/
  char *Save1, *Save2;

  Save1 = s1;
  Save2 = s2;

  //確認用出力
  //printf("s1: %c(%d), s2: %c(%d)\n", *s1, *s1, *s2, *s2);
  //printf("\n");

  //s2に文字列が入っていなかった場合
  if(*s2 == NULL)
  {
    //printf("return -> %c\n", *Save1);
    return(Save1);
  }

  while(*Save1 != NULL)
    {
      //検索したい先頭のポインタをs1に代入
      //検索されるべき先頭のポインタをs2に代入
      s1 = Save1;
      s2 = Save2;

      while(*s1 == *s2)
      {
        /*確認用出力*/
        //printf("Save1: %c, s1: %c, s2: %c\n", *Save1, *s1, *s2);

        s1++;
        s2++;
        
        if(*s2 == NULL)
          {
            /*確認用出力*/
            //printf("return -> %c\n", *Save1);
        
            return (Save1);
          }
      }
	
      Save1++;
      //printf("Save1++;\n");
    }

  return (NULL);
}

void test_strstr1(const char *s1, const char *s2)
{
  char *p;
  p = strstr1(s1, s2);
  if (p == NULL)
    printf("[%s], [%s] -> [NULL]\n", s1, s2);
  else
    printf("[%s], [%s] -> [%s]\n", s1, s2, p);
}

int main(void)
{
  test_strstr1("abcdddef", "dde");
  test_strstr1("abcabc", "abc");
  test_strstr1("abc", "");
  test_strstr1("", "");
  test_strstr1("age:20, name:tom", "name:");
  test_strstr1("This is a pen", "never");
  return (0);
}
