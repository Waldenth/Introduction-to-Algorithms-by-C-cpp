#include "maze.cpp"
void test()
{
    PathType path;
    InitPath(path);
    MazePath_Recursion(1, 1, 8, 8, path);
}
int main()
{
    test();
    system("PAUSE");
    return 0;
}