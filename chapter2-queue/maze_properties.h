#define M 8
#define N 8
const int MaxSize = M * N + 1;
typedef struct 
{
    int i; //Number of rows in the current block
    int j; //Number of columns in the current block
    int pre; //previous walked block's serial number in queue
}Box;
typedef Box ElemType;