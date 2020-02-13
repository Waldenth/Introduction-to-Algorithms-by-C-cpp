#define M 8
#define N 8
const int MaxSize = M * N;
int count = 0;
typedef struct 
{
    int i;
    int j;
}Box;
typedef struct 
{
    Box data[MaxSize];
    int length;
}PathType;



