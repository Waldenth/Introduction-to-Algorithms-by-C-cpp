#include <stdio.h>
#include <stdlib.h>
typedef struct 
{
    char *sq;
    int length;//sq[0...length-1]is data, sq[length]='\0'
}squence;

void InitArray_int(int **&x,int n,int m)
{
    x = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n;i++)
    {
        x[i] = (int *)malloc(sizeof(int) * m);
    }
    return;
}

void InitArray_char(char **&x,int n,int m)
{
    x = (char **)malloc(sizeof(char *) * n);
    for (int i = 0; i < n;i++)
    {
        x[i] = (char *)malloc(sizeof(char) * m);
    }
    for (int i = 0; i < n;i++)
    {
        for (int j = 0; j < m;j++)
        {
            x[i][j] = ' ';
        }
    }

    return;
}

void Lcs_length(squence X,squence Y,int **&c,char **&b)
{
    int m = X.length;
    int n = Y.length;
    InitArray_char(b, m+2, n+2);
    InitArray_int(c, m + 1, n + 1);
    for (int i = 0; i < m + 1;i++)
    {
        c[i][0] = 0;
    }
    for (int j = 0; j < n + 1;j++)
    {
        c[0][j] = 0;
    }
    for (int i = 0; i < m;i++)
    {
        for (int j = 0; j < n;j++)
        {
            if(X.sq[i]==Y.sq[j])
            {
                c[i + 1][j + 1] = c[i][j] + 1;
                b[i + 1][j + 1] = '\\' ;//Upper left Arrow
            }
            else if(c[i][j+1]>=c[i+1][j])
            {
                c[i + 1][j + 1] = c[i][j + 1];
                b[i + 1][j + 1] = '^';//Directly up 
            }
            else
            {
                c[i + 1][j + 1] = c[i + 1][j];
                b[i + 1][j + 1] = '<'; //Left
            }
        }
    }
    return;
}

void Print_LCS(char **b,squence X,int i,int j)
{
    if(i==0&&j==0)
    {
        printf("\n");
        return;
    }
    if (i == 0||j==0)
        return;

    if(b[i][j]=='\\')
    {
        Print_LCS(b, X, i - 1, j - 1);
        printf("%c ", X.sq[i - 1]);
    }
    else if(b[i][j]=='^')
    {
        Print_LCS(b, X, i - 1, j);
    }
    else
    {
        Print_LCS(b, X, i, j - 1);
    }
}

void test()
{
    squence A;
    squence B;
    A.length = 7;
    B.length = 6;

    A.sq = (char *)malloc(sizeof(char) * (A.length + 1));
    B.sq = (char *)malloc(sizeof(char) * (B.length + 1));

    char forA[8] = "ABCBDAB";
    char forB[7] = "BDCABA";

    for (int i = 0; i < A.length;i++)
        A.sq[i] = forA[i];
    for (int j = 0; j < B.length;j++)
        B.sq[j] = forB[j];

    int **c = NULL;
    char **b = NULL;

    Lcs_length(A, B, c, b);
    Print_LCS(b, A, A.length, B.length);
    printf("\n");

    for (int i = 0; i <= A.length;i++)
    {
        for (int j = 0; j <= B.length;j++)
        {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    for (int i = 1; i <= A.length;i++)
    {
        for (int j = 1; j <= B.length;j++)
        {
            printf("%c ", b[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

int main()
{
    test();
    system("PAUSE");
    return 0;
} 
