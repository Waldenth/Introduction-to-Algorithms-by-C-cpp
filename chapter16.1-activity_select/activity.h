#include <stdio.h>
#include <stdlib.h>
#define N 11
typedef struct 
{
    int s;
    int f;
}activity;

int S[N] = {1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12};
int F[N] = {4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16};
activity A[N];

void Init()
{
    for (int i = 0; i < N;i++)
    {
        A[i].s = S[i];
        A[i].f = F[i];
    }
}

activity* Union_operation(activity A[],int Alength,activity B[],int Blength,int &newlength)
{
    activity *newset = (activity *)malloc(sizeof(activity) * Alength);
    for (int i = 0; i < Alength;i++)
        newset[i] = A[i];
    int k = Alength;
    bool flag = true;
    for (int i = 0; i < Blength;i++)
    {
        flag = true;
        for (int j = 0; j < k;j++)
            if(newset[j].f==B[i].f && newset[j].s==B[i].s)
            {
                flag = false;
                break;
            }
        if(flag)
        {
            newset = (activity *)realloc(newset, sizeof(activity) * (k + 1));
            newset[k] = B[i];
            k++;
        }
    }
    newlength = k;
    return newset;
}