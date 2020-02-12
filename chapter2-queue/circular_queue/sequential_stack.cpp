#include <stdlib.h>

//typedef struct {}ElemType;
typedef int data; 

typedef struct 
{
    ElemType data[MaxSize];
    int top;
}SqStack;

void InitStack(SqStack *&s)
{
    s = (SqStack *) malloc(sizeof(SqStack));
    s->top = -1;
    return;
}
void DestoryStack(SqStack*&s)
{
    free(s);
    return;
}
bool StackEmpty(SqStack*s)
{
    return (s->top == -1);//if <s> is empty,return true
}
bool Push(SqStack*&s,ElemType e)
{
    if(s->top==MaxSize-1)
        return false;
    s->top++;
    s->data[s->top] = e;
    return true;
}
bool Pop(SqStack *&s,ElemType&e)
{
    if(s->top==-1)
        return false;
    e = s->data[s->top];
    s->top--;
    return true;
}
bool GetTop(SqStack*s,ElemType&e)
{
    if(s->top==-1)
        return false;
    e = s->data[s->top];
    return true;
}

