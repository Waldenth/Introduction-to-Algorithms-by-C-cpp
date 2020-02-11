#define M 8
#define N 8
const int MaxSize = M * N;
typedef struct 
{
    int i; //Number of rows in the current block
    int j; //Number of columns in the current block
    char di; //next walkable block direction
}Box;
typedef Box ElemType;