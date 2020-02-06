#include <stdio.h>
#include <stdlib.h>
#define INF 0x3f3f3f3f

int PriceList[11] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

int Maxof2(int a,int b)
{
    return (a >= b) ? (a) : (b);
}

int Cut_rod(int n)//自顶向下的递归实现
{
    if(n==0)
        return 0;
    int q = -INF;
    for (int i = 1; i <= n;i++)
    {
        q = Maxof2(q, PriceList[i] + Cut_rod(n - i));
    }
    return q;
}

int Memoized_Cut_rod_Aux(int n,int r[])//带备忘录的自顶向下法
{
    if(r[n]>=0)
        return r[n];//检查备忘录
    int q = -INF;
    if(n==0)
        q = 0;
    else
    {
        for (int i = 1; i <= n;i++)
        {
            q = Maxof2(q, PriceList[i] + Memoized_Cut_rod_Aux(n - i, r));
        }
    }
    r[n] = q;//备忘录记录
    return q;
}
int Memoized_Cut_rod(int n)//带备忘录的自顶向下法
{
    int *r = (int *)malloc(sizeof(int)*(n+1));
    for (int i = 0; i <= n;i++)
        r[i] = -INF;
    return Memoized_Cut_rod_Aux(n, r);
}

int Bottom_up_Cut_rod(int n)//自底向上法
{
    int *r = (int *)malloc(sizeof(int) * (n + 1));
    r[0] = 0;
    for (int j = 1; j <= n;j++)
    {
        int q = -INF;
        for (int i = 1; i <= j;i++)
        {
            q = Maxof2(q, PriceList[i] + r[j - i]);
        }
        r[j] = q;
    }
    return r[n];
}

//Restructure solution
int Extended_Bottom_Up_Cut_rod(int n,int*&s)
{
    int *r = (int *)malloc(sizeof(int) * (n + 1));
    s = (int *)malloc(sizeof(int) * (n + 1));
    r[0] = 0;
    for (int j = 1; j <= n;j++)
    {
        int q = -INF;
        for (int i = 1; i <= j;i++)
        {
            if(q < PriceList[i] + r[j-i])
            {
                q = PriceList[i] + r[j - i];
                s[j] = i;
            }
        }
        r[j] = q;
    }
    return r[n];
}
int Print_Cut_rod_Solution(int n)
{
    int *s = NULL;
    int r=Extended_Bottom_Up_Cut_rod(n,s);
    while(n>0)
    {
        printf("%d ", s[n]);
        n = n - s[n];
    }
    printf("\n");
    return r;
}

void test1()
{
    int length = 14;
    int r=Memoized_Cut_rod(length);
    printf("%d\n", r);
    r = Cut_rod(length);
    printf("%d\n",r);
    r = Bottom_up_Cut_rod(length);
    printf("%d\n",r);
    r = Print_Cut_rod_Solution(length);
    printf("%d\n", r);
}

int main()
{
    test1();
    system("PAUSE");
    return 0;
}