#include "maze.cpp"
void test()
{
    if(!MazePath_Queue(1,1,M,N))
        printf("Not found\n");
}
int main()
{
    test();
    system("PAUSE");
    return 0;
}