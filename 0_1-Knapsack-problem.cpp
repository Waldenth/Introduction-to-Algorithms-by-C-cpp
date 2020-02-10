#include <stdio.h>
#include <stdlib.h>
typedef struct 
{
    int back;
    bool load;
}throwback;



int **InitArray(int n, int m)
{
    int **p = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++)
    {
        p[i] = (int *)malloc(sizeof(int) * m);
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            p[i][j] = 0;
        }
    }
    return p;
}

int Knapsack(int weight[], int value[], int n, int capacity, throwback **&form)
{
    int p;
    int **A = InitArray(n + 1, capacity + 1);
    for (int i = 0; i <= capacity; i++)
        A[0][i] = 0;
    for (int i = 0; i <= n; i++)
        A[i][0] = 0;
    
    for (int i = 1; i <= n; i++)
    {
        p = i - 1;
        for (int j = 1; j <= capacity; j++)
        {
            if (weight[p] > j)
            {
                A[i][j] = A[i - 1][j];
                form[i][j].back = j;
                form[i][j].load = false;
            }
            else
            {
                if (A[i - 1][j] >= A[i-1][j - weight[p]] + value[p])
                {
                    A[i][j] = A[i - 1][j];
                    form[i][j].back = j;
                    form[i][j].load = false;
                }
                else
                {
                    A[i][j] = A[i-1][j - weight[p]] + value[p];
                    form[i][j].back = j - weight[p];
                    form[i][j].load = true;
                }
            }
        }
    }

    for (int i = 0; i <= n;i++)
    {
        for (int j = 0; j <= capacity;j++)
        {
            printf("%2d ", A[i][j]);
        }
        printf("\n");
    }

    return A[n][capacity];
}

void PrintResult(int n,int capacity,throwback**form)
{
    int *result = (int *)malloc(sizeof(int) * (n));
    int j = capacity;
    for (int i = n; i >= 1;i--)
    {
        if(form[i][j].load)
        {
            result[i - 1] = 1;
        }
        else
        {
            result[i - 1] = 0;
        }
        j=form[i][j].back;
    }
    for (int i = 0; i < n;i++)
    {
        printf("%d ", result[i]);
    }
    printf("\n");
    return;
}




void test()
{
    int weight[5] = {2, 2, 6, 5, 4};
    int value[5] = {6, 3, 5, 4, 6};
    int capacity = 10;
    throwback **form = (throwback **)malloc(sizeof(throwback *) * (5 + 1));
    for (int i = 0; i <= 5;i++)
    {
        form[i] = (throwback *)malloc(sizeof(throwback) * 11);
    }

    int sum = Knapsack(weight, value, 5, capacity, form);
    printf("%d\n", sum);
    PrintResult(5, capacity, form);
}

int main()
{
    test();
    system("PAUSE");
    return 0;
}
