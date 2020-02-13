#include "maze_properties.h"
#include <stdlib.h>
//typedef struct{}ElemType

typedef struct 
{
    ElemType data[MaxSize];
    int front, rear;
}SqQueue;

void InitQueue(SqQueue*&q)
{
    q = (SqQueue *)malloc(sizeof(SqQueue));
    q->front = q->rear = -1;
    return;
}
void DestoryQueue(SqQueue*&q)
{
    free(q);
}
bool QueueEmpty(SqQueue*q)
{
    return (q->front == q->rear);
}
bool enQueue(SqQueue *&q,ElemType e)
{
    if(q->rear==MaxSize-1)
        return false;
    q->rear++;
    q->data[q->rear] = e;
    return true;
}
bool deQueue(SqQueue*&q,ElemType&e)
{
    if(q->front==q->rear)
        return false;
    q->front++;
    e = q->data[q->front];
    return true;
}
