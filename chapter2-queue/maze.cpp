#include "sequential_queue.cpp"
#include <stdio.h>
int maze[M + 2][N + 2] =
    {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 1, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

void print(SqQueue*qu,int front)
{
    int k = front;
    int j;
    int ns = 0;
    printf("\n");
    do
    {
        j = k;
        k = qu->data[k].pre;
        qu->data[j].pre = -1;
    } while (k != 0);
    printf("One of the shortest maze path is as follows:\n");
    k = 0;
    while(k<MaxSize)
    {
        if(qu->data[k].pre==-1)
        {
            ns++;
            printf("\t(%d,%d)", qu->data[k].i, qu->data[k].j);
            if(ns%5==0)
                printf("\n");
        }
        k++;
    }
    printf("\n");
}


bool MazePath_Queue(int xi,int yi,int xe,int ye)//Find path from (xi,yi) to (xj,yj) in maze
{
    Box e;
    int i, j, nexti, nextj;
    char di;
    SqQueue *qu;
    InitQueue(qu);
    e.i = xi;
    e.j = yi;
    e.pre = -1;
    enQueue(qu, e);
    maze[xi][yi] = -1;
    while(!QueueEmpty(qu))
    {
        deQueue(qu, e);
        i = e.i;
        j = e.j;
        if(i==xe&&j==ye)
        {
            print(qu, qu->front);
            DestoryQueue(qu);
            return true;
        }
        di = 'A'-1;
        while(di < 'D')
        {
            di++;
            switch (di)
            {
            case 'A':
                nexti = i - 1;
                nextj = j;
                break;
            case 'B':
                nexti = i;
                nextj = j + 1;
                break;
            case 'C':
                nexti = i + 1;
                nextj = j;
                break;
            case 'D':
                nexti = i;
                nextj = j - 1;
                break;
            default:
                printf("Direction Error\n");
                system("PAUSE");
                break;
            }
            if(maze[nexti][nextj]==0)
            {
                e.i = nexti;
                e.j = nextj;
                e.pre = qu->front;
                enQueue(qu, e);
                maze[nexti][nextj] = -1;
            }
        }
    }
    DestoryQueue(qu);
    return false;
}