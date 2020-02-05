#define INF 0x3f3f3f3f
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