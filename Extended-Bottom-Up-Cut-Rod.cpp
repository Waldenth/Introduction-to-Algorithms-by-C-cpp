/*
ǰ������ĸ����и̬�滮�㷨���ص������Ž�����ֵ��
����û�з��ؽ�ı��������������չ���� 
*/

#include <stdio.h>
#include <stdlib.h>
#define INF 32767

void Extended_Bottom_Up__Cut_Rod(int *answer,int p[],int n)
{
	int *r=(int*)malloc(sizeof(int)*(n+1));//��¼����Ϊj�ĸֹ�һ�ηָ��������� 
	int *s=(int*)malloc(sizeof(int)*(n+1));//���ָֹܵļ�¼���� 
	r[0]=0;//����Ϊ0������Ϊ0 
	for(int j=1;j<=n;j++)//�Գ���Ϊj�ĸֹ����ŵ�һ�ηָ���м��� 
	{
		int q=-INF;
		for(int i=1;i<=j;i++)
		{
			if(q<p[i]+r[j-i])//�г�һ������i�Ĺ��� (ֱ�����������ٸ�),�ⲿ������Ϊp[i],ʣ�¹��ӳ�j-i���������ŷ����� ,����Ϊr[j-i] 
			{
				q=p[i]+r[j-i];//������� 
				s[j]=i;//����Ϊj�ĸֹ�һ�����ŷָ���ֱ����������һ�γ��ȣ����� 
				r[j]=q;//����Ϊj�ĸֹ�һ�ηָ������������� 
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
	while(n>0)//���ֹܻ����Լ����ָ� 
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
	getchar();
}
