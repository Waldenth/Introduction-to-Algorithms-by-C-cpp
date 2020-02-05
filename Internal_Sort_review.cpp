/*
假设关键字类型为短整型int
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int KeyType;
//typedef <> InfoType;
typedef struct
{
    KeyType key;
    //InfoType data;    //其他数据项
} RecType;

/*插入排序
插入排序的基本实现是:每次将一个待排序的元素按照关键字大小插入到前面
已经排好序的子表中的适当位置上。直到全部元素插入完成为止。
这类似于打扑克时抽到新牌后理牌时将抽的新牌插入到自己手上的牌扇中
*/
//Straight insertion sort
//直接插入排序
//取出无序区的第一个元素,在有序区中线性查找合适的位置将该元素插入
void InsertSort_Straight(RecType R[], int n) //对R[0...n-1]进行递增排序
{
    int i, j;
    RecType temp;
    for (i = 1; i < n; i++) //依次插入
    {
        temp = R[i];
        j = i-1;
        while (j >= 0 && R[j].key > temp.key)
        {
            R[j + 1] = R[j];
            j--;
        }
        R[j + 1] = temp;
    }
}

//Binary insertion sort
//折半插入排序
//优化在有序区的查找方式,由于有序区有序，可以使用二分查找方式查找合适的插入位置
void InsertSort_Binary(RecType R[], int n) //对R[0...n-1]进行递增排序
{
    int i, j;
    RecType temp;
    int left, right, mid;
    for (i = 1; i < n; i++)
    {
        temp = R[i];
        left = 0;
        right = i - 1;
        while (left <= right)
        {
            mid = (left + right) / 2;
            if (temp.key < R[mid].key)
            {
                right = mid - 1;
                continue;
            }
            else
            {
                left = mid + 1;
                continue;
            }
        }
        for (j = i - 1; j >= right + 1; j--)
        {
            R[j + 1] = R[j];
        }
        R[right + 1] = temp;
    }
}

//Shell Sort
//希尔排序
//类似于将插入排序与分组归并排序结合的一种排序算法
/*
    基本思想:取一个小于n的整数d1,作为第一个增量,把表中的元素
    分成d1组,将所有距离为d1的元素归于一个组，对每个组进行直接插入排序
    直到最后d=1,即整体为一个组,排序完成
    */
void ShellSort(RecType R[], int n) //取d1=(n/2)的递增希尔排序
{
    int i, j, d;
    RecType temp;
    d = n / 2;
    while (d > 0)
    {
        for (i = d; i < n; i++)
        {
            temp = R[i];
            j = i - d;
            while (j >= 0 && temp.key < R[j].key) //该组元素反序时
            {
                R[j + d] = R[j];
                j = j - d;
            }
            R[j + d] = temp;
        }
        d = d / 2;
    }
}

/*交换排序
交换排序的基本思想是两两比较待排序元素的关键字,如果两个元素的次序相反
则进行交换。直到没有元素反序为止。
*/
//Bublle sort
//冒泡排序
//最经典、流传最广、最为流行、但又最"臭名昭著"的算法
/*
    基本思想:通过无序区中相邻的元素关键字间的比较和位置的交换使得
    关键字最小的元素如同气泡一样逐渐漂浮到水面上
    */
void swap(RecType *a, RecType *b)
{
    RecType temp = *a;
    *a = *b;
    *b = temp;
}
//没有flag的冒泡排序
void BubbleSort_No_Flag(RecType *R, int n) //对R[0...n-1]进行55递增排序
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = n - 1; j > i; j--) //找到气泡,冒到位置R[i]上
            if (R[j].key < R[j - 1].key)
                swap(&R[j], &R[j - 1]);
}

/*
    在有些情况下,可能几趟冒泡之后就已经排好序了,如果加入哨兵,
    就可以提前终止算法.
    有flag的冒泡排序.
    */
void BubbleSort_Flag(RecType *R, int n) //对R[0...n-1]进行递增排序
{
    int i, j;
    bool exchange;
    for (i = 0; i < n - 1; i++)
    {
        exchange = false;
        for (j = n - 1; j > i; j--)
        {
            if (R[j].key < R[j - 1].key)
            {
                swap(&R[j], &R[j - 1]);
                exchange = true;
            }
        }
        if (!exchange)
            return;
    }
}

//QuickSort
//快速排序
/*
    快排由冒泡排序改进得到.设计非常的精妙.
    基本思想:在待排序的n个元素中任取一个元素作为基准(随机一般效果较好)
    把这个元素放到应在的位置后,整个序列被其划分成两个部分,
    对这两个部分继续重复上述操作.如此循环递归.
    */

int partition(RecType R[], int left, int right) //对R[left....right]进行一趟划分
{
    int i = left;
    int j = right;
    RecType temp = R[i];
    while (i < j)
    {
        while (j > i && R[j].key >= temp.key) //从右向左扫描,找到第一个比基准小的元素
        {
            j--;
        }
        R[i] = R[j];                          //原基准位放入这个元素
        while (i < j && R[i].key <= temp.key) //再从左向右扫描,找到第一个比基准大的元素
        {
            i++;
        }
        R[j] = R[i]; //放入右部分中的异常位置
    }
    R[i] = temp; //基准归位
    return i;    //返回中心位
}

void QuickSort(RecType R[], int left, int right) //对R[left....right]非递减排序
{
    int i;
    if (left < right)
    {
        i = partition(R, left, right);
        QuickSort(R, left, i - 1);
        QuickSort(R, i + 1, right);
    }
}

/*
选择排序
选择排序的基本思想是每一趟从待排序的元素中选择关键字最小的元素,
放在已经排好序的子表最后,直到全部元素排序完毕.
选择排序的精髓在于选择策略和数据预处理
*/
//Simple Selection Sort
//简单选择排序
/*
    基本思想是在第i趟排序开始时,当前有序区和无序区分别为:
    R[0..i-1]和R[i..n-1]
    该趟排序就是从当前无序区选出关键字最小的元素R[k],将它和无序区
    第1个元素进行交换,这样R[0..i]就成了新的有序区.
    如此不断扩大有序区范围直至全部有序.
    */
void SelectSort(RecType R[], int n) ////对R[0...n-1]进行非递减排序
{
    int i, j, k;
    for (i = 0; i < n - 1; i++)
    {
        k = i;
        for (j = i + 1; j < n; j++)
        {
            if (R[j].key < R[k].key)
            {
                k = j;
            }
        }
        if (k != i)
            swap(&R[i], &R[k]);
    }
}

//Heap Sort
//堆排序
/*
    堆是一种特殊有趣的数据结构,堆结合了树和队列的各自特点,
    可看作一个几乎完全的二叉树
    每个节点都满足这样的特性:
    任一父节点的键值(key)不小于子节点的键值。

    这里堆排非递减序列,采用大根堆.
*/

void Sift_down(RecType *H, int i, int length) //if H[i]<H[2i] or H[i]<H[2i+1],Move down H[i] so that make H[i]>=H[2i] and H[2i+1]
{
    //logical length
    int Identify = 0;
    if (2 * i + 1 > length - 1) //This node is a leaf node
        return;
    while (2 * i + 1 <= (length - 1) && Identify == 0)
    {
        i = 2 * i + 1;
        if (i + 1 <= length - 1 && (H[i + 1].key > H[i].key))
        {
            i = i + 1; //choose the bigger son node
        }
        if (H[(i - 1) / 2].key < H[i].key)
        {
            RecType temp = H[(i - 1) / 2];
            H[(i - 1) / 2] = H[i];
            H[i] = temp;
        }
        else
            Identify = 1;
    }
    return;
}

void MakeHeap(RecType *A, int length) //logical length
{
    for (int i = length / 2 - 1; i >= 0; i--)
    {
        Sift_down(A, i, length);
    }
}

void HeapSort(RecType R[], int n) //n is logical length
{
    int i = n;
    while (i >= 1)
    {
        MakeHeap(R, i);
        RecType temp = R[0];
        R[0] = R[i - 1];
        R[i - 1] = temp;
        i--;
    }
}

/*
归并排序
多次将两个或者两个以上的有序表合并成一个新的有序表.
*/

//2-way merge sort
/*
    基本思路是将R[0....n-1]看成是n个长度为1的有序序列
    然后进行两两归并.
    */
void Merge(RecType *A, int p, int q, int r) ////A[p..q..r], A[p..q] and A[q+1..r] have been sorted
{
    RecType *temp = (RecType *)malloc(sizeof(RecType) * (r - p + 1));
    int i = p;
    int j = q + 1;
    int k = 0;
    while (i <= q && j <= r)
    {
        if (A[i].key <= A[j].key)
        {
            temp[k] = A[i];
            i++;
            k++;
        }
        else
        {
            temp[k] = A[j];
            j++;
            k++;
        }
    }
    if (i <= q)
    {
        for (int w = i; w <= q; w++)
        {
            temp[k] = A[w];
            k++;
        }
    }
    else
    {
        for (int w = j; w <= r; w++)
        {
            temp[k] = A[w];
            k++;
        }
    }
    for (int i = p; i <= r; i++)
    {
        A[i] = temp[i - p];
    }
}

void Merge_Sort(RecType *A, int p, int r) //sort A[p....r]
{
    if (p < r)
    {
        int q = (p + r) / 2;
        Merge_Sort(A, p, q);
        Merge_Sort(A, q + 1, r);
        Merge(A, p, q, r);
    }
}

/*
基数排序
与基于关键字之间的比较不同,基数排序(radix sort)是通过分配和收集过程
进行排序,不需要进行关键字之间的比较.
*/

//LSD最低位优先排序法 Least significant digit first,LSD

//需要设置最大的关键字位数MAXV,这里设为5
#define MAXD 5

typedef struct node
{
    char data[MAXD];
    struct node *next;
} NodeType; //基数排序数据的结点类型

void RadixSort(NodeType *&p, int r, int d) //LSD基数排序算法
{
    NodeType *head[MAXD], *tail[MAXD], *t;
    int i, j, k;
    for (i = 0; i <= d - 1; i++) //从低位到高位的循环
    {
        for (j = 0; j < r; j++) //初始化各个链队的首尾指针
        {
            head[j] = tail[j] = NULL;
        }
        while (p != NULL)
        {
            k = p->data[i] - '0'; //找到第k个链队
            if (head[k] == NULL)
            {
                head[k] = p;
                tail[k] = p; //如果该队为空,队头和队尾均指向p
            }
            else //不为空则结点p进队
            {
                tail[k]->next = p;
                tail[k] = p;
            }
            p = p->next; //取下一个待排序的元素
        }
        p = NULL;               //重新利用p来收集所有的结点
        for (j = 0; j < r; j++) //对每一个链队进行收集
        {
            if (head[j] != NULL) //非空链队
            {
                if (p == NULL) //如果第j个链队是第一个非空链队
                {
                    p = head[j];
                    t = tail[j];
                }
                else //第j个链队是其他非空链队
                {
                    t->next = head[j]; //加入队列
                    t = tail[j];       //迁移指针
                }
            }
        }
        t->next = NULL;
    }
}

/*
桶排序
bucket sort
*/
void BucketSort(RecType *R,int n)//对R[0...n-1]进行非递减排序
{
    int min = 0x3f3f3f3f;
    int max = -1;
    int c = 0;
    int fx = -1;
    for (int i = 0; i < n;i++)
    {
        if(R[i].key>max)
            max = R[i].key;
        if(R[i].key<min)
            min = R[i].key;
    }
    int k = max/10 - min / 10 + 1;
    c = min / 10;
    RecType **A = (RecType **)malloc(sizeof(RecType *) * k);
    for (int i = 0; i < k;i++)
    {
        A[i] = NULL;
    }//设置空桶

    int *B = (int *)malloc(sizeof(int) * k);
    for (int i = 0; i < k;i++)
    {
        B[i] = 0;
    }//每个桶内的数据个数

    for (int i = 0; i < n; i++)
    {
        fx = R[i].key / 10 - c;
        B[fx]++;
        //printf("fx=%d B[fx]=%d\n", fx, B[fx]);
        A[fx] = (RecType *)realloc(A[fx], sizeof(RecType) * B[fx]);
        A[fx][B[fx] - 1] = R[i];
    }//装桶

    /*
	for(int i=0;i<k;i++)
	{
        printf("-> ");
        for(int j=0;j<B[i];j++)
		{
			printf("%d ",A[i][j].key);
		}
		printf("\n");
	}
    */
    for (int i = 0; i < k;i++)
    {
        InsertSort_Binary(A[i], B[i]);
    }
    fx = 0;
    for (int i = 0; i < k;i++)
    {
        for (int j = 0; j < B[i];j++)
        {
            R[fx] = A[i][j];
            fx++;
        }
    }
}


void test_1()
{
    time_t seed;
	srand((unsigned int)time(&seed));
    int N;
    scanf("%d", &N);
    RecType *R = (RecType *)malloc(sizeof(RecType) * N);
    for (int i = 0; i < N;i++)
    {
        R[i].key = rand() % (N * 10);
    }
    for (int i = 0; i < N;i++)
        printf("%d ", R[i].key);
    printf("\n");

    BucketSort(R,N);
    
    for (int i = 0; i < N;i++)
        printf("%d ", R[i].key);
    printf("\n");
}
int main()
{
    test_1();
    system("PAUSE");
    return 0;
}
