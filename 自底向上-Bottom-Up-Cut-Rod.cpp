/*
15.1钢条分割 P204 
*/ 
#include <stdio.h>
#include <stdlib.h>

int max(int x,int y)
{
	if(x>=y)
		return x;
	else
		return y;
}

int Bottom_Up_Cut_Rod(int p[],int n)//自底向上的动态规划算法 
{
	int *r=(int *)malloc(sizeof(int)*(n+1));//Let r[0...n]be a new array
	r[0]=0;
	for(int j=1;j<=n;j++)
	{
		int q=-32767;
		for(int i=1;i<=j;i++)
		{
			q=max(q,p[i]+r[j-i]);
			printf(" q=%d ",q);
		}
		r[j]=q;
		printf("r=%d\n",r[j]);
	}
	return r[n];
}

int main()
{
	int p[11]={0,1,5,8,9,10,17,17,20,24,30};
	printf("%d \n",Bottom_Up_Cut_Rod(p,4));
}
