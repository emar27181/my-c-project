#include <stdio.h>
void hanoi(int n, char *from, char *to, char *tmp);

int main(void)
{
    hanoi(3, "a", "b", "c");
    return (0);
}

void hanoi(int n, char *from, char *to, char *tmp)
{
    

    if (n == 0)
        return;

    else{
    //n枚目とその他(上のn-1枚)でそれぞれ動きを分けて考える
    //まず、移動元と移動先を考えて、残りを一時待機場所にするイメージ

    //(n枚目を目的地に移動させるために)上の(n - 1)枚を元の場所(from)から一時待機場所に移動(tmp)に移動させる
    hanoi(n - 1, from, tmp, to);

    //n枚目を目的地(to)に移動させる
    printf("move disk %d from %s to %s\n", n, from, to);

    //移動させておいた(n - 1)枚を一時待機場所(tmp)から目的地(to)に移動させる
    hanoi(n - 1, tmp, to, from);
    }
}