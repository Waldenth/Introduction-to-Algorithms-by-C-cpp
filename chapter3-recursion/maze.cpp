#include "maze_properties.h"
#include <stdio.h>
#include <stdlib.h>
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

void InitPath(PathType&path)
{
    path.length = 0;
    return;
}

void MazePath_Recursion(int xi,int yi,int xe,int ye,PathType path)
{
    int di, k, i, j;
    if(xi==xe&&yi==ye)
    {
        path.data[path.length].i = xi;
        path.data[path.length].j = yi;
        path.length++;
        int enter = 0;
        printf("The %d Maze path is as follows:\n",++count);
        for (k = 0; k < path.length;k++)
        {
            printf("\t(%d,%d)", path.data[k].i, path.data[k].j);
            enter++;
            if(enter==5)
            {
                if(k!=path.length-1)
                    printf("\n");
                enter = 0;
            }
        }
        printf("\n");
    }
    else
    {
        if(maze[xi][yi]==0)
        {
            di = 0;
            while(di<4)
            {
                path.data[path.length].i = xi;
                path.data[path.length].j = yi;
                path.length++;
                switch (di)
                {
                case 0:
                    i = xi - 1;
                    j = yi;
                    break;
                case 1:
                    i = xi;
                    j = yi + 1;
                    break;
                case 2:
                    i = xi + 1;
                    j = yi;
                    break;
                case 3:
                    i = xi;
                    j = yi - 1;
                    break;
                default:
                    printf("Direction error\n");
                    system("PAUSE");
                    break;
                }
                maze[xi][yi] = -1;
                MazePath_Recursion(i, j, xe, ye, path);
                maze[xi][yi] = 0;
                path.length--;
                di++;
            }
        }
    }
    
}