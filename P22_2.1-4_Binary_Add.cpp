#include <stdio.h>
#include <stdlib.h>
int add_binary_number(int*a,int*b,int n,int *&c)
{
    c = (int *)malloc(sizeof(int) * (n + 1));
    int carry_flag = 0;
    for (int i = n - 1; i >= 0;i--)
    {
        c[i + 1] = (carry_flag ^ a[i] ^ b[i]);
        carry_flag = (carry_flag & (a[i] ^ b[i])) | (a[i] & b[i]);
    }
    c[0] = carry_flag;
    return n + 1;
}

void test_BinAdder()
{
    int a[5] = {0, 1, 1, 0, 1};
    int b[5] = {0, 0, 1, 1, 1};
    int *c;
    
    printf("  ");
    for (int i = 0; i < 5;i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");

    printf("  ");
    for (int i = 0; i < 5;i++)
    {
        printf("%d ", b[i]);
    }
    printf("\n");

    int m = add_binary_number(a, b, 5, c);
    for (int n = 0; n < m;n++)
    {
        printf("%d ", c[n]);
    }
    printf("\n");
}
int main()
{
    test_BinAdder();
    system("PAUSE");
    return 0;
}