#include <stdio.h>
#include <stdlib.h>
#define INF 0x3f3f3f3f

//Find the maximum subarray of the form A[MaxLeft..mid..MaxRight]
//the subarray MUST contain A[mid]
int Find_max_crossing_subarray(int *A,int low,int mid,int high,int *MaxLeft,int *MaxRight)
{
    int left_sum=-INF;
    int right_sum = -INF;
    int sum = 0;
    for (int i = mid; i >= low;i--)
    {
        sum += A[i];
        if(sum>left_sum)
        {
            left_sum = sum;
            *MaxLeft = i;
        }
    }
    sum = 0;//Reset sum for finding in the right
    for (int i = mid + 1; i <= high;i++)
    {
        sum += A[i];
        if(sum>right_sum)
        {
            right_sum = sum;
            *MaxRight = i;
        }
    }
    return (left_sum + right_sum);
}

//Find max subarray from A[low...high]
int Find_maximum_subarray(int A[],int low,int high,int *MaxLeft,int *MaxRight)
{
    if(low==high)//only an element
    {
        *MaxRight = high;
        *MaxLeft = low;
        return A[low];
    }
    else
    {
        int mid = (low + high) / 2;
        int left_low, left_high, left_sum;
        int right_low, right_high, right_sum;
        int cross_low, cross_high, cross_sum;
        
        left_sum = Find_maximum_subarray(A, low, mid, &left_low, &left_high);
        right_sum = Find_maximum_subarray(A, mid + 1, high, &right_low, &right_high);

        cross_sum = Find_max_crossing_subarray(A, low, mid, high, &cross_low, &cross_high);

        if(left_sum>=right_sum&&left_sum>=cross_sum)//Max_subarray in the left
        {
            *MaxLeft = left_low;
            *MaxRight = left_high;
            return left_sum;
        }
        else if(right_sum>=left_sum&&right_sum>=cross_sum)//Max_subarray in the right
        {
            *MaxLeft = right_low;
            *MaxRight = right_high;
            return right_sum;
        }
        else
        {
            *MaxLeft = cross_low;
            *MaxRight = cross_high;
            return cross_sum;
        }
    }
}

//Find max subarray from A[low...high]
int Find_maximum_subarray_enumerate(int A[],int low,int high,int *MaxLeft,int *MaxRight)
{
    int sum = -INF;
    for (int i = low; i <= high;i++)
    {
        for (int j = i; j <= high;j++)
        {
            int tmp_sum = 0;
            int k = i;
            while(k<=j)
            {
                tmp_sum += A[k];
                k++;
            }
            if(sum<tmp_sum)
            {
                sum = tmp_sum;
                *MaxLeft = i;
                *MaxRight = j;
            }
        }
    }
    return sum;
}

//Find max subarray from A[low...high]
int Find_maximum_subarray_DP(int A[],int low,int high,int *MaxLeft,int *MaxRight)
{
    int *B = (int *)malloc(sizeof(int)*(high-low+1));
    int sum = A[low];
    B[0] = A[low];
    *MaxRight = low;
    *MaxLeft = low;
    int tmp_left=0;
    int tmp_right=0;
    for (int i = low + 1; i <= high;i++)
    {
        if(B[i-low-1]>=0)
        {
            B[i - low] = B[i-low-1] + A[i];
            tmp_right = i;
        }
        else
        {
            B[i - low] = A[i];
            tmp_right = i;
            tmp_left = i;
        }
        if(B[i-low]>sum)
        {
            sum = B[i - low];
            *MaxLeft = tmp_left;
            *MaxRight = tmp_right;
        }
    }
    return sum;
}

int main()
{
    int A[16] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    int left = -1;
    int right = -1;
    int sum = 0;
    sum = Find_maximum_subarray(A, 0, 15, &left, &right);
    printf("A[%d,%d] is the maximum subarray,which is %d\n", left, right, sum);

    sum = Find_maximum_subarray_enumerate(A, 0, 15, &left, &right);
    printf("A[%d,%d] is the maximum subarray,which is %d\n", left, right, sum);

    sum = Find_maximum_subarray_DP(A, 0, 15, &left, &right);
    printf("A[%d,%d] is the maximum subarray,which is %d\n", left, right, sum);

    system("PAUSE");
}