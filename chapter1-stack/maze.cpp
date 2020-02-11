#include "sequential_stack.cpp"
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

bool MazePath_Stack(int xi,int yi,int xe,int ye)//Find path from (xi,yi) to (xe,ye) in maze
{
    SqStack *st;
    InitStack(st);
    Box e;
    Box path[MaxSize];
    int i, j;
    int nexti, nextj;
    char di;
    bool find = false;
    e.i = xi, e.j = yi, e.di = 'A'-1;
    Push(st, e);
    maze[xi][yi] = -1;
    while (!StackEmpty(st))
    {
        GetTop(st, e);
        i = e.i, j = e.j;
        di = e.di;
        if(i==xe&&j==ye)//find path
        {
            printf("One maze path is as follows:\n");
            int k = 0;
            while(!StackEmpty(st))
            {
                Pop(st, e);
                path[k++] = e;
            }
            int enter = 0;
            while (k>=1)
            {
                k--;
                enter++;
                printf("\t(%d,%d)", path[k].i, path[k].j);
                if(enter==5)
                {
                    enter = 0;
                    printf("\n");
                }
            }
            printf("\n");
            DestoryStack(st);
            return true;
        }
        find = false;
        while(di<='D'&&!find)
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
            case 'E':
            	break;
            default:
                printf("Direction Error\n");
                system("PAUSE");
                break;
            }
            if(maze[nexti][nextj]==0)
                find = true;
        }
        if(find)
        {
            st->data[st->top].di = di;
            e.i = nexti;
            e.j = nextj;
            e.di = 'A' - 1;
            Push(st, e);
            maze[nexti][nextj] = -1;
        }
        else
        {
            Pop(st, e);
            maze[e.i][e.j] = 0;
        }
        
    }
    DestoryStack(st);
    return false;
}
