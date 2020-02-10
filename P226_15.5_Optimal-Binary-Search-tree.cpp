#include <stdio.h>
#include <stdlib.h>
#define INF 0x3f3f3f3f

void InitArray_int(int **&a,int n,int m)
{
    a = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n;i++)
    {
        a[i] = (int *)malloc(sizeof(int) * m);
    }
    return;
}

void InitArray_float(float **&a,int n,int m)
{
    a = (float **)malloc(sizeof(float *) * n);
    for (int i = 0; i < n;i++)
    {
        a[i] = (float *)malloc(sizeof(float) * m);
    }
    return;
}

void Optimal_Bst(float **&e,int **&root,float p[],float q[],int n)//p[1...n],q[0...n]
{
    InitArray_float(e, n + 2, n + 2);
    InitArray_int(root, n + 1, n + 1);
    float **w = NULL;
    InitArray_float(w, n + 2, n + 2);

    for (int i = 1; i <= n + 1;i++)
    {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }
    for (int L = 1; L <= n;L++)
    {
        for (int i = 1; i <= n - L + 1;i++)
        {
            int j = i + L - 1;
            e[i][j] = INF;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            for (int r = i; r <= j;r++)
            {
                float t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if(t<e[i][j])
                {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }
    return;
}

void test()
{
    float p[6] = {0, 0.15, 0.10, 0.05, 0.10, 0.20};
    float q[6] = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
    float **e = NULL;
    int **root = NULL;
    Optimal_Bst(e, root, p, q, 5);

    for (int i = 1; i <= 6;i++)
    {
        for (int j = i - 1; j <= 5;j++)
        {
            printf("%.2f ", e[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 1; i <= 5;i++)
    {
        for (int j = i; j <= 5;j++)
        {
            printf("%d ", root[i][j]);
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
