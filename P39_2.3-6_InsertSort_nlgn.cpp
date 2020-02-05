#include <stdio.h>
#include <stdlib.h>
#include <time.h>|

void INSERTION_SORT_B(int A[],int length)
{
    int key = -1;

    int left = 0;
    int right = -1;
    int mid = 0;

    for (int j = 1; j < length;j++)
    {
        key = A[j];
        left = 0;
        right = j - 1;
        while(left<=right)
        {
            mid = (left + right) / 2;
            if(A[mid]>key)
            {
                right = mid - 1;
                continue;
            }
            else 
            {
                left = mid + 1;
                continue;
            }
        }
        for (int k = j - 1; k >= right+1;k--)
        {
            A[k + 1] = A[k];
        }
        A[right + 1] = key;
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

	INSERTION_SORT_B(A, N);

	for (int i = 0; i < N;i++)
		printf("%d ", A[i]);
	printf("\n");

	system("PAUSE");
	return 0;
}

