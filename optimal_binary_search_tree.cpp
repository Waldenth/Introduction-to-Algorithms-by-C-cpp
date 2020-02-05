#include <stdio.h>
#include <stdlib.h>
#define INF 10000
int OPTILMAL_BST(int p[],int q[],int n)//概率列表p1...pn,q0,q1...qn
{
    int **e;
    int **w;
    int **root;
    e=(int **)malloc(sizeof(int *)*(n+2));
    w=(int **)malloc(sizeof(int*)*(n+2));
    root=(int **)malloc(sizeof(int*)*(n+2));
    for(int i=0;i<=n+1;i++)
    {
        e[i]=(int *)malloc(sizeof(int)*(n+1));
        w[i]=(int *)malloc(sizeof(int)*(n+1));
        root[i]=(int *)malloc(sizeof(int)*(n+1));
    }
    for(int i=1;i<=n+1;i++)
    {
        e[i][i-1]=q[i-1];
        w[i][i-1]=q[i-1];
    }
    for(int l=1;l<=n;l++)//计算的子树的结点个数(可理解为长度)
    {
        for(int i=1;i<=n-l+1;i++)
        {
            int j=i+l-1;//i号到j号，一共l个结点
            e[i][j]=INF;
            w[i][j]=w[i][j-1]+p[j]+q[j];//w[i][j]表示一个树(i号到j号结点构成)在成为一个结点(i=<r<=j)的子树时的增加的期望搜索代价
            /*
            注意，由二叉搜索树的性质，i~j号结点的根节点是其中的一个结点r,(因为根节点左子树结点编号小于它，右子树大于它，这是由于已经排好序了再编的号)
            */
            for(int r=i;r<=j;r++)
            {
                int t=e[i][r-1]+e[r+1][j]+w[i][j];
                if(t<e[i][j])
                {
                    e[i][j]=t;
                    root[i][j]=r;
                }
            }
        }
    }
    printf("e[i][j]=\n");
    for(int i=1;i<=n+1;i++)
    {
        for(int j=i-1;j<=n;j++)
        {
            printf("%d ",e[i][j]);
        }
        printf("\n");
    }
    printf("w[i][j]=\n");
    for(int i=1;i<=n+1;i++)
    {
        for(int j=i-1;j<=n;j++)
        {
            printf("%d ",w[i][j]);
        }
        printf("\n");
    }
    printf("root[i][j]=\n");
    for(int i=1;i<=n+1;i++)
    {
        for(int j=i;j<=n;j++)
        {
            printf("%d ",root[i][j]);
        }
        printf("\n");
    }


    return root[1][n];     
}
int main()
{
    int p[6]={INF,15,10,5,10,20};//n=5
    int q[6]={5,10,5,5,5,10};
    OPTILMAL_BST(p,q,5);



    printf("你好，世界！\n");
    getchar();
}
