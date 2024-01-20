//最終更新: 2021/05/17

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//コマンド引数などの情報を出力する関数
void conf_print(int argc, char *argv[])
{
    printf("argc = %d\n", argc);
    for (int i = 0; i < argc; i++)
    {
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    printf("-------------------------\n\n");
}

//ファイルに入っている文字を出力する関数
//n_option: nオプションを有効にするかを保存する変数
//line: ファイル内の出力行が何行目かを保存する変数
//check_print: ファイルの出力が行われたかを確認するための変数
int print_file(FILE *fp, int n_option, int h_option, int t_option, int line, int h_num, int t_num, int check_print, int check_stdio)
{
    //c: 文字コードを保存する変数
    //check_new_line: cが改行を保存しているかどうかを保存する変数
    //line_before: それまでに何行出力したかを保存する変数
    //word_count: それまでに何文字出力したかを保存する変数
    int c, check_new_line = 0, line_before, word_count = 0;

    //確認用出力
    //printf("\nlinebefore = %d\n", line);
    //line_before = line;

    //確認用出力
    //printf("n_option = %d, h_option = %d, t_option = %d, h_num = %d, t_num = %d\n", n_option, h_option, t_option, h_num, t_num);

    //標準入出力の実行(1行目のみ例外的実行)
    if (check_stdio == 1 && line == 1)
    {
        if ((h_option == 0 || (h_option == 1 && h_num <= line)) && (t_option == 0 || (t_option == 1 && line <= t_num))){}
        if (n_option == 1)
        {
            c = getc(fp);
            printf("     %d	", line);
            putc(c, stdout);
        }
    }

    //-nオプションの実行(各ファイルの1行目のみ例外的実行)
    else if (h_option == 0 || (h_option == 1 && h_num == 1) || check_print == 1)
    {
        if (n_option == 1)
        {
            printf("     %d	", line);
        }
    }

    //最初の文字の代入
    c = getc(fp);

    while (c != EOF)
    {
        //行数の加算
        if (c == '\n')
        {
            check_new_line = 1;
            line++;
        }

        if ((h_option == 0 || (h_option == 1 && h_num <= line)) && (t_option == 0 || (t_option == 1 && line <= t_num)))
        {
            //cの標準出力
            putc(c, stdout);
            word_count++;
        }

        //次の文字の代入
        c = getc(fp);

        //-nオプションの実行
        if ((h_option == 0 || (h_option == 1 && h_num <= line)) && (t_option == 0 || (t_option == 1 && line <= t_num)))
        {
            if (n_option == 1 && check_new_line == 1 && c != EOF)
            {
                printf("     %d	", line);
            }
        }

        //check_new_lineのリセット
        check_new_line = 0;
    }

    //改行
    //printf("\n");

    //確認用出力
    //printf("\nlinebefore = %d, line = %d\n", line_before, line);

    //lineのリターン
    return (line);
}

int main(int argc, char *argv[])
{
    //変数の宣言
    //fp: 展開するファイルへのポインタ
    //n_option: -nオプションが呼び出されているかを確認するための変数
    //h_option: -hオプションが呼び出されているかを確認するための変数
    //t_option: -tオプションが呼び出されているかを確認するための変数
    //check_print: ファイルの出力が行われたかを確認するための変数
    //check_stdio: 標準入出力で呼び出されているかどうかを確認する変数
    //line: 今までの出力行が何行目かを保存する変数
    //h_num: 出力行の最初の行数を保存する変数 (1 <= h_num < n) (※n: ファイルの行数)
    //t_num: 出力行の最後の行数を保存する変数 (1 < t_num <= n)
    FILE *fp = NULL;
    int n_option = 0, h_option = 0, t_option = 0, check_print = 0, check_stdio = 0, line = 1, h_num = 0, t_num = 0;
    char *p;

    //確認用出力
    //conf_print(argc, argv);

    //"./a.out"のみの入力なので標準入出力を実行して終了"
    if (argc == 1)
    {
        check_stdio = 1;
        print_file(stdin, n_option, h_option, t_option, line, h_num, t_num, check_print, check_stdio);
        exit(1);
    }

    //""./a.out"以外の入力があった場合
    for (int i = 1; i < argc; i++)
    {
        //ファイルの展開
        fp = fopen(argv[i], "r");

        //argv[i]がファイルの名前だった場合、ファイルの内容の出力
        if (fp != NULL)
        {
            line = print_file(fp, n_option, h_option, t_option, line, h_num, t_num, check_print, check_stdio);
            check_print = 1;
        }

        //-n optionの確認
        else if ((strcmp(argv[i], "-n")) == 0)
        {
            n_option = 1;
        }

        //-h optionの確認と指定数字(出力開始行数)の確認
        else if (strncmp(argv[i], "-h", 2) == 0)
        {
            h_option = 1;

            //ポインタを3文字目に指すように移動
            argv[i] = argv[i] + 2;

            //3文字目の文字を整数型に変換しh_numに代入
            h_num = atoi(argv[i]);

            //確認用出力
            //printf("3rd word(-h): %s\n", argv[i]);
            //printf("%d\n", atoi(argv[i]));
        }

        //-t optionの確認と指定数字(出力終了行数)の確認
        else if (strncmp(argv[i], "-t", 2) == 0)
        {
            t_option = 1;

            //ポインタを3文字目に指すように移動
            argv[i] = argv[i] + 2;

            //3文字目の文字を整数型に変換しt_numに代入
            t_num = atoi(argv[i]);
        }

        //-n, -h, -t以外のオプションが呼び出されたときのエラー出力
        else if (strncmp(argv[i], "-", 1) == 0)
        {
            fprintf(stderr, "%s: %s: This is invalid option. please input n or h or t\n", argv[0], argv[i]);
            exit(1);
        }

        //意味のない文字列が入っていたのでエラー出力
        else
        {
            fprintf(stderr, "%s: %s: No such file or directory\n", argv[0], argv[i]);
            exit(1);
        }
    }

    //ファイルの内容の出力が行われていないので、標準入出力を実行して終了
    if (check_print == 0)
    {
        check_stdio = 1;
        print_file(stdin, n_option, h_option, t_option, line, h_num, t_num, check_print, check_stdio);
        return (0);
    }

    //改行
    printf("\n");

    return(0);
}