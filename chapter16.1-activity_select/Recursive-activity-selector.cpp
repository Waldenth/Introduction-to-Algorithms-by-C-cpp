#include "activity.h"
activity*Recursive_activity_selector(activity A[],int k,int Alength,int &length)//Initial state k=0
{
    int m = k + 1;
    if(k==0)
    {
        activity a[1] = {A[0]};
        int Blength = 0;
        activity *b = Recursive_activity_selector(A, m, Alength,Blength);
        return Union_operation(a, 1, b, Blength,length);
    }
    else
    {
        while (m<Alength&&A[m].s<A[k].f)
        {
            m++;
        }
        if(m<Alength)
        {
            activity a[1] = {A[m]};
            int Blength = 0;
            activity *b = Recursive_activity_selector(A, m, Alength, Blength);
            return Union_operation(a, 1,b,Blength, length);
        }
        else
            return NULL;
    }
}

int main()
{
    Init();
    int length = 0;
    activity*result=Recursive_activity_selector(A, 0, N, length);
    for (int i = 0; i < length;i++)
    {
        printf("\t(%d,%d)", result[i].s, result[i].f);
    }
    printf("\n");
    system("PAUSE");
    return 0;
}