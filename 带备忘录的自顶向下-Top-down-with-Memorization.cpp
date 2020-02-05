#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#define INF 32767
int max(int a,int b)
{
	if(a>=b)
		return a;
	else
		return b;
}

int Memorized_Cut_Rod_Aux(int p[],int n,int r[])
{
	int q=-INF;
	if(r[n]>=0)//�ݹ���� 
	{
		return r[n];	
	}	
	else if(n==0)//���뺯���ĸֹܳ���Ϊ0 
	{
		q=0;
	}
	else
	{
		for(int i=1;i<=n;i++)
		{
			q=max(q,p[i]+Memorized_Cut_Rod_Aux(p,n-i,r));//һ�ηָ� 
		}
	}
	r[n]=q;
	return q;
}

int Memorized_Cut_Rod(int p[],int n)
{
	int *r=(int*)malloc(sizeof(int)*(n+1));
	for(int i=0;i<=n;i++)
	{
		r[i]=-INF;
	}
	return Memorized_Cut_Rod_Aux(p,n,r); 
}
int main()
{
	int p[11]={0,1,5,8,9,10,17,17,20,24,30};
	printf("%d \n",Memorized_Cut_Rod(p,4));
}
