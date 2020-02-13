#include "goods.h"
#include <stdio.h>
#include <stdlib.h>

float Greedy_knaspack(int *&plan, float value[], float weight[], int capacity)
{
    float value_performance[N];
    for (int i = 0; i < N; i++)
        value_performance[i] = value[i] / weight[i];
    bool goods[N] = {true, true, true, true, true};
    plan = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
        plan[i] = 0;
    float sumvalue = 0;
    while (capacity > 0)
    {
        int choose = -1;
        float tempvalue = 0;
        for (int i = 0; i < N; i++)
        {
            if (goods[i])
            {
                if (value_performance[i] > tempvalue)
                {
                    tempvalue = value_performance[i];
                    choose = i;
                }
            }
        }
        if (capacity >= weight[choose])
        {    
            capacity -= weight[choose];
            sumvalue += value[choose];
            goods[choose] = false;
            plan[choose] = weight[choose];
        }
        else
        {
            sumvalue += capacity * value_performance[choose];
            goods[choose] = false;
            plan[choose] = capacity;
            capacity = 0;
        }
    }
    return sumvalue;
}

int main()
{
    int *plan;
    float sum = Greedy_knaspack(plan, value, weight, 100);
    printf("select plan:\n");
    for (int i = 0; i < N;i++)
    {
        printf("\t%d", plan[i]);
    }
    printf("\nTotal value=%.2f\n", sum);
    system("PAUSE");
    return 0;
}