#include "maze.cpp"
void test()
{
    if(!MazePath_Stack(1, 1, 8, 8))
        printf("Not found\n");
}

int main()
{
    test();
    system("PAUSE");
    return 0;
}
