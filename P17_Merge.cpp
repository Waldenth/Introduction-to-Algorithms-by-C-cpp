#include <stdlib.h>
#define INF 0x3f3f3f3f
void Merge(int *A,int p,int q,int r)//A[p..q..r], A[p..q] and A[q+1..r] have been sorted
{
    int n1 = q - p + 1;
    int n2 = r - q;
    int *L = (int *)malloc(sizeof(int) * (n1 + 1));
    int *R = (int *)malloc(sizeof(int) * (n2 + 1));
    for (int i = 0; i < n1;i++)
    {
        L[i] = A[p + i];
    }
    for (int j = 0; j < n2;j++)
    {
        R[j] = A[q + j + 1];
    }

    L[n1] = R[n2] = INF;
    int i = 0;
    int j = 0;
    for (int k = p; k <= r;k++)
    {
        if(L[i]<=R[j])
        {
            A[k] = L[i];
            i++;
        }
        else
        {
            A[k] = R[j];
            j++;
        }
    }
}