/*
前面给出的钢条切割动态规划算法返回的是最优解收益值，
但并没有返回解的本身，下面给出扩展方法 
*/

#include <stdio.h>
#include <stdlib.h>
#define INF 32767

void Extended_Bottom_Up__Cut_Rod(int *answer,int p[],int n)
{
	int *r=(int*)malloc(sizeof(int)*(n+1));//记录长度为j的钢管一次分割的最大收益 
	int *s=(int*)malloc(sizeof(int)*(n+1));//划分钢管的记录数组 
	r[0]=0;//长度为0，收益为0 
	for(int j=1;j<=n;j++)//对长度为j的钢管最优的一次分割进行计算 
	{
		int q=-INF;
		for(int i=1;i<=j;i++)
		{
			if(q<p[i]+r[j-i])//切出一个长度i的管子 (直接卖掉，不再割),这部分收益为p[i],剩下管子长j-i，根据最优方案来 ,收益为r[j-i] 
			{
				q=p[i]+r[j-i];//收益更新 
				s[j]=i;//长度为j的钢管一次最优分割后的直接卖出的那一段长度，更新 
				r[j]=q;//长度为j的钢管一次分割的最优收益更新 
			}
		}
	}
	for(int w=1;w<=n;w++)
	{
		answer[w]=s[w];
	}
}

void Print_Cut_Rod_Solution(int p[],int n,int *s)
{
	while(n>0)//当钢管还可以继续分割 
	{
		printf("%d ",s[n]);
		n=n-s[n];
	}
}


int main()
{
	int p[11]={0,1,5,8,9,10,17,17,20,24,30};
	int n=4;
	int *answer=(int *)malloc(sizeof(int)*(n+1));
	answer[0]=0;
	Extended_Bottom_Up__Cut_Rod(answer,p,n);
	for(int i=0;i<n;i++)
		printf("%d ",answer[i]);
	printf("\n");
	Print_Cut_Rod_Solution(p,n,answer);
}
