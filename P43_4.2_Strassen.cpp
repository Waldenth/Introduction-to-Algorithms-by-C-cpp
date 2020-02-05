#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int **cells = NULL;
    int rows;
} matrix;

void Init_matrix(matrix &A)
{
    int rows;
    scanf("%d", &rows);
    A.rows = rows;
    A.cells = (int **)malloc(sizeof(int) * A.rows);
    for (int i = 0; i < A.rows; i++)
    {
        *(A.cells + i) = (int *)malloc(sizeof(int) * A.rows);
    }
    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j < A.rows; j++)
        {
            scanf("%d", &A.cells[i][j]);
        }
    }
    return;
}

void Init_matrix1(matrix &A, int rows)
{
    A.rows = rows;
    A.cells = (int **)malloc(sizeof(int) * A.rows);
    for (int i = 0; i < A.rows; i++)
    {
        *(A.cells + i) = (int *)malloc(sizeof(int) * A.rows);
    }
    return;
}

void partion(matrix A, matrix &a11, matrix &a12, matrix &a21, matrix &a22)
{
    int mid = A.rows / 2;
    Init_matrix1(a11, mid);
    Init_matrix1(a12, mid);
    Init_matrix1(a21, mid);
    Init_matrix1(a22, mid);

    for (int i = 0; i < mid; i++)
        for (int j = 0; j < mid; j++)
        {
            a11.cells[i][j] = A.cells[i][j];
        }
    for (int i = 0; i < mid; i++)
        for (int j = mid; j < A.rows; j++)
        {
            a12.cells[i][j - mid] = A.cells[i][j];
        }
    for (int i = mid; i < A.rows; i++)
        for (int j = 0; j < mid; j++)
        {
            a21.cells[i - mid][j] = A.cells[i][j];
        }
    for (int i = mid; i < A.rows; i++)
        for (int j = mid; j < A.rows; j++)
        {
            a22.cells[i - mid][j - mid] = A.cells[i][j];
        }
    return;
}

matrix Square_matrix_multiply_add(matrix A, matrix B)
{
    matrix c;
    int n = A.rows;
    c.rows = n;
    c.cells = (int **)malloc(sizeof(int) * c.rows);
    for (int i = 0; i < c.rows; i++)
    {
        *(c.cells + i) = (int *)malloc(sizeof(int) * c.rows);
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            c.cells[i][j] = A.cells[i][j] + B.cells[i][j];
        }
    return c;
}

matrix Square_matrix_multiply(matrix A, matrix B)
{
    matrix c;
    c.rows = A.rows;
    c.cells = (int **)malloc(sizeof(int) * c.rows);
    for (int i = 0; i < c.rows; i++)
    {
        *(c.cells + i) = (int *)malloc(sizeof(int) * c.rows);
    }
    for (int i = 0; i < A.rows; i++)
        for (int j = 0; j < A.rows; j++)
        {
            c.cells[i][j] = 0;
            for (int k = 0; k < A.rows; k++)
            {
                c.cells[i][j] += A.cells[i][k] * B.cells[k][j];
            }
        }
    return c;
}

matrix Merge_matrix(matrix c11, matrix c12, matrix c21, matrix c22)
{
    matrix c;
    int n = c11.rows * 2;
    c.rows = n;
    c.cells = (int **)malloc(sizeof(int) * c.rows);
    for (int i = 0; i < c.rows; i++)
    {
        *(c.cells + i) = (int *)malloc(sizeof(int) * c.rows);
    }
    for (int i = 0; i < n / 2; i++)
    {
        for (int j = 0; j < n / 2; j++)
        {
            c.cells[i][j] = c11.cells[i][j];
        }
    }
    for (int i = 0; i < n / 2; i++)
    {
        for (int j = n / 2; j < c.rows;j++)
        {
            c.cells[i][j] = c12.cells[i][j - n / 2];
        }
    }
    for (int i = n / 2; i < c.rows; i++)
    {
        for (int j = 0; j < n / 2; j++)
        {
            c.cells[i][j] = c21.cells[i - n / 2][j];
        }
    }
    for (int i = n / 2; i < c.rows;i++)
    {
        for (int j = n / 2; j < c.rows;j++)
        {
            c.cells[i][j] = c22.cells[i - n / 2][j - n / 2];
        }
    }
}

matrix Square_matrix_multiply_Recursive(matrix A, matrix B)
{
    int n = A.rows;
    matrix c;    
    matrix c11, c12, c21, c22;
    if (n == 1) //base case
        c.cells[0][0] = A.cells[0][0] * B.cells[0][0];
    else
    {
        matrix a11, a12, a21, a22;
        matrix b11, b12, b21, b22;   
        matrix tmp1, tmp2;

        partion(A, a11, a12, a21, a22);
        partion(B, b11, b12, b21, b22);

        tmp1 = Square_matrix_multiply_Recursive(a11, b11);
        tmp2 = Square_matrix_multiply_Recursive(a12, b21);
        c11 = Square_matrix_multiply_add(tmp1, tmp2);

        tmp1 = Square_matrix_multiply_Recursive(a11, b12);
        tmp2 = Square_matrix_multiply_Recursive(a12, b22);
        c12 = Square_matrix_multiply_add(tmp1, tmp2);

        tmp1 = Square_matrix_multiply_Recursive(a21, b11);
        tmp2 = Square_matrix_multiply_Recursive(a22, b21);
        c21 = Square_matrix_multiply_add(tmp1, tmp2);

        tmp1 = Square_matrix_multiply_Recursive(a21, b12);
        tmp2 = Square_matrix_multiply_Recursive(a22, b22);
        c22 = Square_matrix_multiply_add(tmp1, tmp2);
    }
    c = Merge_matrix(c11, c12, c21, c22);
    return c;
}

int main()
{
    matrix A;
    matrix B;
    Init_matrix(A);
    Init_matrix(B);
    matrix c = Square_matrix_multiply(A, B);
    for (int i = 0; i < c.rows; i++)
    {
        for (int j = 0; j < c.rows; j++)
        {
            printf("%d ", c.cells[i][j]);
        }
        printf("\n");
    }
    system("PAUSE");
    return 0;
}
