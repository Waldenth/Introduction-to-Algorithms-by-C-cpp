#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
int BinarySearch_R(int A[],int p,int q,int target)//to find target from A[p....q]  Recursion
{
    int mid = (p + q) / 2;
    if(A[mid]==target)
    {
        return mid;
    }
    else if(A[mid]>target)
    {
        return BinarySearch_R(A, p, mid - 1, target);
    }
    else
    {
        return BinarySearch_R(A, mid + 1, q, target);
    }
    return -1;
}


int BinarySearch_I(int A[],int p,int q,int target)//to find target from A[p....q]  Iteration
{
    int i = p;
    int j = q;
    int mid = 0;
    while(i<=j)
    {
        mid = (i + j) / 2;
        if(A[mid]==target)
        {
            return mid;
        }
        else if(A[mid]>target)
        {
            j = mid - 1;
        }
        else
        {
            i = mid + 1;
        }
    }
    return -1;
}
