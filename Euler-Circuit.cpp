/*
This C(pp) program is used for find an Euler Circuit 
in a Graph which is input by users 
*/
#include <stdio.h>
#include <stdlib.h>
#define MAXV 32767
typedef struct node
{
    int no;
    int find_info;
}AdjNode;

void Create_AdjMatrix(int n,int**&G)
{
    G=(int**)malloc(sizeof(int*)*n);
    for(int i=0;i<n;i++)
    {
        *(G+i)=(int*)malloc(sizeof(int)*n);
        for(int j=0;j<n;j++)
            G[i][j]=0;
        int temp1,temp2;
        for(int j=0;j<n;j++)
        {
            scanf("%d %d",&temp1,temp2);
            temp1--;temp2--;
            *(*(G+temp1)+temp2)=1;
            *(*(G+temp2)+temp1)=1;
        }
    }
}

int main()
{
    int n=-1;
    scanf("%d",&n);
    int **edges=NULL;
    Create_AdjMatrix(n,edges);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            printf("%d ",edges[i][j]);
        printf("\n");
    }
}

