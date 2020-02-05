#include <stdio.h>
#include <stdlib.h>
#include <time.h>|
void INSERTION_SORT(int A[],int length)
{
	for(int j=1;j<length;j++)
	{
		int key=A[j];
		int i=j-1;
		while(i>=0&&A[i]>key)
		{
			A[i+1]=A[i];
			i--;
		}
		A[i+1]=key;
	}
} 
int main()
{
	time_t seed;
	srand((unsigned int)time(&seed));
	int N = 0;
	scanf("%d", &N);
	int *A = (int *)malloc(sizeof(int) * N);
	for (int a = 0; a < N;a++)
	{
		A[a] = rand() % (N * 10);
	}
	for (int i = 0; i < N;i++)
		printf("%d ", A[i]);
	printf("\n");

	INSERTION_SORT(A, N);

	for (int i = 0; i < N;i++)
		printf("%d ", A[i]);
	printf("\n");

	system("PAUSE");
	return 0;
}

