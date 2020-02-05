#include <stdio.h>
#include <stdlib.h>
#define INF 100000
//15.2矩阵链乘法
int Matrix_Chain_Order(int p[],int n)//[p0,p1....pn]
//1号矩阵行数p0,列数p1   n号矩阵行数pn-1列数pn 
{
	int length=n+1;
	
	int **m;
	int **s;
	//m,s用于: 	m[i][j]存放i到j号矩阵相乘的最小代价 
	//		   	s[i][j]存放m[i][j]对应的最优分割点	
	
	m=(int**)malloc(sizeof(int*)*(length));
	s=(int**)malloc(sizeof(int*)*(length));
	for(int i=0;i<=n;i++)
	{
		m[i]=(int *)malloc(sizeof(int )*length);
		s[i]=(int *)malloc(sizeof(int )*length);
	}
	for(int i=0;i<=n;i++)
		for(int j=0;j<=n;j++)
		{
			m[i][j]=-1;
			s[i][j]=-1;
		}
	for(int i=1;i<=n;i++)
		m[i][i]=0;//i号矩阵到i号矩阵所需的计算当然为0次 
	for(int len=2;len<=n;len++)//len是目前计算的一个矩阵链的长度 
	{
		for(int i=1;i<=n-len+1;i++)
		{
			int j=i+len-1;//从i号开始到j号构成的矩阵链，由于长度为len,所以j的编号就是i+len-1	
			/*
			m[i][j]的计算只依赖于i到j中那些长度小于j-i+1 (就是j-i+1个矩阵)的子链的最优计算代价 
			*/
			m[i][j]=INF; 
			for(int k=i;k<=j-1;k++)//分割点， 将矩阵链分为i...k号和k+1...j号 
			{
				int q=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
				if(q<m[i][j])
				{
					m[i][j]=q;
					s[i][j]=k;
					
				}
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
		{
			printf("%d ",m[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			printf("%d ",s[i][j]);
		}
		printf("\n");
	}
		
	return m[1][n];
}

int main()
{
	//printf("%d",INF);
	int p[7]={30,35,15,5,10,20,25};
	int w=Matrix_Chain_Order(p,6);
	printf("w=%d",w);
}




