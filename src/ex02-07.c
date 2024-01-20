#include <stdio.h>
#include <stdlib.h>

int atoi1(const char *str)
{   
    int num = 0, minus = 0; 

    while(*str != NULL)
    {   
        /*num: 整数値を保存する変数*/
        if(*str == '-'){
            minus = 1;

            /*確認用出力
            printf("minus = 1\n");
            */
        }


        if(*str >= '0' && *str <= '9'){
            num = num * 10 +  (*str - '0');
        }
        str++;
    }
    
    if(minus == 1){
        return(-num);
    }

    else if (minus == 0){
        return(num);
    }
}

int main(void)
{
    char str1[] = "135";
    char str2[] = "-100";
    int i,j;
    i = atoi1(str1);
    j = atoi1(str2);
    printf("(%d) + (%d) = %d \n", i, j, i+j);
    return (0);
}