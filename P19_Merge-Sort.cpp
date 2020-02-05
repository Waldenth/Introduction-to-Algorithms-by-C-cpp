//#include "P17_Merge.cpp"
#include <stdio.h>
#include <time.h>
#include "P39_2.3-2_Merge_no_sentry.cpp"
#include "P39_2.3-5_Binary_search.cpp"

void Merge_Sort(int *A,int p,int r)//sort A[p....r]
{
    if(p < r)
    {
        int q = (p + r) / 2;
        Merge_Sort(A, p, q);
        Merge_Sort(A, q + 1, r);
        Merge(A, p, q, r);
    }
}

void test()
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

    int target = A[0];

    Merge_Sort(A, 0, N - 1);

    for (int i = 0; i < N;i++)
		printf("%d ", A[i]);
	printf("\n");

    printf("%d\n", BinarySearch_I(A, 0, N - 1, target)+1);
}

int main()
{
    test();
    system("PAUSE");
}