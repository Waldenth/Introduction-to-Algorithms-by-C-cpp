#include <stdlib.h>
#include <stdio.h>
void Merge(int *A,int p,int q,int r)////A[p..q..r], A[p..q] and A[q+1..r] have been sorted
{
    int *temp = (int *)malloc(sizeof(int) * (r - p + 1));
    int i = p;
    int j = q + 1;
    int k = 0;
    while(i<=q&&j<=r)
    {
        if(A[i]<=A[j])
        {
            temp[k] = A[i];
            i++;
            k++;
        }
        else
        {
            temp[k] = A[j];
            j++;
            k++;
        }
    }
    if(i<=q)
    {
        for (int w = i; w <= q;w++)
        {
            temp[k] = A[w];
            k++;
        }
    }
    else
    {
        for (int w = j; w <= r;w++)
        {
            temp[k] = A[w];
            k++;
        }
    }
    for (int i = p; i <= r; i++)
    {
        A[i] = temp[i - p];
    }
}
