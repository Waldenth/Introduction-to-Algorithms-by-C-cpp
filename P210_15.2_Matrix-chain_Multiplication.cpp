#include <stdio.h>
#include <stdlib.h>
#define INF 0x3f3f3f3f
typedef struct matrix
{
    int columns;
    int rows;
    int **cells;
}matrix;

matrix Matrix_multiply(matrix A,matrix B)
{
    if(A.columns!=B.rows)
    {
        printf("Incompatible dimensions!\n");
        system("PAUSE");
    }
    else
    {
        matrix C;
        C.rows = A.rows;
        C.columns = B.columns;
        C.cells = (int **)malloc(sizeof(int *) * (C.rows));
        for (int i = 0; i < C.rows;i++)
            C.cells[i] = (int *)malloc(sizeof(int) * C.columns);
        for (int i = 0; i < A.rows;i++)
        {
            for (int j = 0; j < B.columns;j++)
            {
                C.cells[i][j] = 0;
                for (int k = 0; k < A.columns;k++)
                {
                    C.cells[i][j] += A.cells[i][k] + B.cells[k][j];
                }
            }
        }
        return C;
    }
}

int **InitTables(int n,int m)//<n> rows / <m> columns
{
    int **s = (int **)malloc(sizeof(int*) * n);
    for (int j = 0; j < m;j++)
    {
        s[j] = (int *)malloc(sizeof(int) * m);
    }
    for (int i = 0; i < n;i++)
    {
        for (int j = 0; j < m;j++)
        {
            s[i][j] = 0;
        }
    }
    return s;
} 

void Output_upper_triangle(int **A,int n)//A[0..n-1 x 0..n-1]
{
    for (int i = 0; i < n;i++)
    {
        for (int j = i; j <n ;j++)
        {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int Matrix_chain_Order(int p[],int n)//ATTENTION p[0,...,n]
//p.length=n+1
{
    int **m = InitTables(n, n);
    int **s = InitTables(n - 1, n - 1);
    for (int L = 2; L <= n;L++)//L is chain length
    {
        for (int i = 1; i <= n - L + 1;i++)
        {
            int j = i + L - 1;
            m[i-1][j-1] = INF;
            for (int k = i; k <= j - 1;k++)
            {
                int q = m[i - 1][k - 1] + m[k + 1 - 1][j - 1] + p[i - 1] * p[k] * p[j];
                if(q<m[i-1][j-1])
                {
                    m[i-1][j-1] = q;
                    s[i-1][j-1] = k;
                }
            }
        }
    }
    Output_upper_triangle(m, n);
    Output_upper_triangle(s, n - 1);
    return m[0][n - 1];
}

void test1()
{
    int p[7] = {30, 35, 15, 5, 10, 20, 25};
    int sum = Matrix_chain_Order(p, 6);
    printf("%d\n", sum);
}

int main()
{
    test1();
    system("PAUSE");
    return 0;
}
