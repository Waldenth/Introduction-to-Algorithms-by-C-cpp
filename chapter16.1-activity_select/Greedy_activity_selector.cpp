#include "activity.h"
activity*Greedy_activity_selector(activity A[],int Alength,int &length)
{
    int n = Alength;
    activity *B = (activity *)malloc(sizeof(activity));
    int Blength = 1;
    B[0] = A[0];
    int k = 0;
    for (int m = 1; m < n; m++)
    {
        if (A[m].s >= A[k].f)
        {
            activity am[1] = {A[m]};
            B = Union_operation(B, Blength, am, 1, Blength);
            k = m;
        }
    }
    length = Blength;
    return B;
}

int main()
{
    Init();
    int length = 0;
    activity *result = NULL;
    result=Greedy_activity_selector(A, N, length);
    for (int i = 0; i < length;i++)
    {
        printf("\t(%d,%d)", result[i].s, result[i].f);
    }
    printf("\n");
    system("PAUSE");
    return 0;
}
