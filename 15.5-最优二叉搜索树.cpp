#include <stdio.h>
#include <stdlib.h>

int OPTIMAL_BST(int p[],int q[],int n)//p1,p2....pn /   q0,q1....qn
{
    int**e;
    int**w;
    e=(int **)malloc(sizeof(int *)*(n+2));
    w=(int **)malloc(sizeof(int *)*(n+2));
    for(int i=0;i<=n+1;i++)
    {
        e[i]=(int*)malloc(sizeof(int)*(n+1));
        w[i]=(int*)malloc(sizeof(int*)*(n+1));
    }
    for(int l=1;l<=n;l++)
    {
        for(int i=1;i<=n-l+1;i++)
        {
            
        }
    }


}

int main()
{
    printf("Hello,World!你好\n");
}
