# 排序
所谓排序，是整理表中的记录，使之按关键字递增（或递减）有序排列.
说明：排序数据中可以存在相同关键字的记录.这里仅考虑递增(非递减)排序.
## 内排序
在排序过程中，若整个表都是放在内存中处理，排序时不涉及数据的内、外存交换，则称之为内排序；
## 外排序
反之，若排序过程中要进行数据的内、外存交换，则称之为外排序.

这里暂时只分析内排序.
## 内排序分类（部分）
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200129140418864.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dhbGRlbnRo,size_16,color_FFFFFF,t_70)

# 各类排序算法介绍
所用数据结构:
为简单起见，本文大部分算法采用顺序表作为排序数据的存储结构，并假设关键字类型为短整型

排序算法的稳定性:
如果待排序的表中有多个关键字相同的元素，在排序后这些元素的相对次序保持不变，则这个排序算法是稳定(stable)的。
排序算法的稳定性有其意义所在，通俗的说，比如商品的销量和利润两个关键字，商家当然希望优先选择销量高同时利润高的商品优先进货.如果采用稳定排序算法，则不需要任何处理，直接对这两个关键字按照主次进行两遍排序即可.


```c
/*
假设关键字类型为短整型int
*/
typedef int KeyType;
//typedef <> InfoType;

typedef struct
{
    KeyType key;
    //InfoType data;    //其他数据项
} RecType;

//LSD最低位优先排序法数据结构体 Least significant digit first,LSD
//需要设置最大的关键字位数MAXV,这里设为5
#define MAXD 5
typedef struct node
{
    char data[MAXD];
    struct node *next;
} NodeType; //基数排序数据的结点类型
```

## 插入排序
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200129140623133.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dhbGRlbnRo,size_16,color_FFFFFF,t_70)
Evernote
插入排序的基本实现是:每次将一个待排序的元素按照关键字大小插入到前面
已经排好序的子表中的适当位置上。直到全部元素插入完成为止。
这类似于打扑克时抽到新牌后理牌时将抽的新牌插入到自己手上的牌扇中.

**Straight insertion sort
直接插入排序**
取出无序区的第一个元素,在有序区中线性查找合适的位置将该元素插入

```c
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
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200129141500737.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dhbGRlbnRo,size_16,color_FFFFFF,t_70)
**Binary insertion sort
折半插入排序**
优化在有序区的查找方式,由于有序区有序，可以使用二分查找方式查找合适的插入位置.

```c
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
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200129141536157.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dhbGRlbnRo,size_16,color_FFFFFF,t_70)
**Shell Sort
希尔排序**
类似于将插入排序与分组归并排序结合的一种排序算法
    **基本思想:取一个小于n的整数d1,作为第一个增量,把表中的元素
    分成d1组,将所有距离为d1的元素归于一个组，对每个组进行直接插入排序
    直到最后d=1,即整体为一个组,排序完成**
    ![在这里插入图片描述](https://img-blog.csdnimg.cn/20200129141652183.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dhbGRlbnRo,size_16,color_FFFFFF,t_70)
```c
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
```
希尔排序的复杂度性能分析较为复杂，目前一般认为是O(n^1.3),并且一般认为，希尔排序的速度通常比直接插入排序快.
## 交换排序
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020012914194420.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dhbGRlbnRo,size_16,color_FFFFFF,t_70)
交换排序的基本思想是两两比较待排序元素的关键字,如果两个元素的次序相反
则进行交换。直到没有元素反序为止。

**Bublle sort
冒泡排序**
最经典、流传最广、最为流行、但又最"臭名昭著"的算法
基本思想:通过无序区中相邻的元素关键字间的比较和位置的交换使得
关键字最小的元素如同气泡一样逐渐漂浮到水面上.

```c
void swap(RecType *a, RecType *b)
{
    RecType temp = *a;
    *a = *b;
    *b = temp;
}
//没有flag的冒泡排序
void BubbleSort_No_Flag(RecType *R, int n) //对R[0...n-1]进行递增排序
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = n - 1; j > i; j--) //找到气泡,冒到位置R[i]上
            if (R[j].key < R[j - 1].key)
                swap(&R[j], &R[j - 1]);
}
```
在有些情况下,可能几趟冒泡之后就已经排好序了,如果加入哨兵,
就可以提前终止算法.
有flag的冒泡排序.

```c
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
```
算法分析
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020012914221798.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dhbGRlbnRo,size_16,color_FFFFFF,t_70)
**QuickSort
快速排序**
快排由冒泡排序改进得到.设计非常的精妙.

**基本思想:在待排序的n个元素中任取一个元素作为基准(随机一般效果较好)
把这个元素放到应在的位置后,整个序列被其划分成两个部分,
对这两个部分继续重复上述操作.如此循环递归.**
划分示例
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200129144241707.gif)

快排是一个非常流行而且高效的算法，其平均时间复杂度为
8(nlogn).  其优于合并排序之处在于它在原位上排序，不需要额外的辅助存贮空间(合并排序需8(n)的辅助空间)。很多程序语言自带的排序算法都是快排算法。同样的，在很多人心中，快速排序算法也是20世纪最伟大的算法之一.
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200129142526676.png)
快排发明者Charles A. R. Hoare 1960 年发布了使他闻名于世的快速排序算法 (Quicksort)，这个算法也是当前世界上使用最广泛的算法之一， 
当时他供职于伦敦一家不大的计算机生产厂家，为产品编写当时新出现的希尔排序算法，他不仅优秀的完成了任务，还发明了更为优越的快速排序算法。1980 年，Hoare 被授予图灵奖，以表彰其在程序语言定义与设计领域的根本性的 贡献。在 2000 年，Hoare 因其在计算机科学和教育方面的杰出贡献被英国皇家封为爵士。

```c
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
```
算法分析
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200129143027142.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dhbGRlbnRo,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200129142943938.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dhbGRlbnRo,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200129142836874.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dhbGRlbnRo,size_16,color_FFFFFF,t_70)

## 选择排序

**选择排序的基本思想是每一趟从待排序的元素中选择关键字最小的元素,
放在已经排好序的子表最后,直到全部元素排序完毕.**
选择排序的精髓在于选择策略和数据预处理.

```c
void swap(RecType *a, RecType *b)
{
    RecType temp = *a;
    *a = *b;
    *b = temp;
}
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
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200129143547785.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dhbGRlbnRo,size_16,color_FFFFFF,t_70)
**Heap Sort
堆排序**
堆是一种特殊有趣的数据结构,堆结合了树和队列的各自特点,堆排序也是一个非常漂亮的算法.
堆可看作一个几乎完全的二叉树
每个节点都满足这样的特性:
任一父节点的键值(key)不小于子节点的键值(大根堆),这里堆排非递减序列,采用大根堆.

```c
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
```
**算法分析**
堆排需要掌握堆的有关预备知识.
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200129144455619.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dhbGRlbnRo,size_16,color_FFFFFF,t_70)

## 归并排序

**基本思路:**
多次将两个或者两个以上的有序表合并成一个新的有序表
最简单的归并是将相邻两个有序的子表合并成一个有序的表，即二路归并排序.

2-way merge sort
基本思路是将R[0....n-1]看成是n个长度为1的有序序列
然后进行两两归并.

```c
void Merge(RecType *A, int p, int q, int r) //A[p..q..r], A[p..q] and A[q+1..r] have been sorted
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
```
算法分析
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200129145345588.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dhbGRlbnRo,size_16,color_FFFFFF,t_70)
归并排序很多时候比快排速度略快，但是快排的一个显著优点则是不需要额外的存储空间，空间复杂度更小.


## 基数排序
**基本思路**
与基于关键字之间的比较不同,基数排序(radix sort)是通过分配和收集过程
进行排序,不需要进行关键字之间的比较.
目前已经证明，按照关键字比较策略的算法最优复杂度为O(nlgn)，不可能有效率更高的算法了.但是基数排序这种策略的排序算法则可以在适合情况下将算法时间复杂度降至O(cn).

这里介绍的是LSD最低位优先排序法 Least significant digit first,LSD、

```c
//LSD最低位优先排序法数据结构体 Least significant digit first,LSD
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
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200129150039714.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dhbGRlbnRo,size_16,color_FFFFFF,t_70)![在这里插入图片描述](https://img-blog.csdnimg.cn/20200129150107111.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dhbGRlbnRo,size_16,color_FFFFFF,t_70)![在这里插入图片描述](https://img-blog.csdnimg.cn/20200129150117666.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dhbGRlbnRo,size_16,color_FFFFFF,t_70)

## 桶排序bucket sort
我不怎么喜欢桶排序，很多玩比赛的朋友很喜欢，可能是某些oj太变态吧....
桶排序 (Bucket sort)或所谓的箱排序，是一个排序算法，工作的原理是将数组分到有限数量的桶子里。每个桶子再个别排序（有可能再使用别的排序算法或是以递归方式继续使用桶排序进行排序）。桶排序是鸽巢排序的一种归纳结果。当要被排序的数组内的数值是均匀分配的时候，桶排序使用线性时间（Θ（n））。但桶排序并不是 比较排序，不受到 O(n log n) 下限的影响。

排序利用函数的映射关系，减少了几乎所有的比较工作。实际上，桶排序的f(k)值的计算，其作用就相当于快排中划分，已经把大量数据分割成了基本有序的数据块(桶)。然后只需要对桶中的少量数据做先进的比较排序即可。
对N个关键字进行桶排序的时间复杂度分为两个部分：
(1) 循环计算每个关键字的桶映射函数，这个时间复杂度是O(N)。
(2) 利用先进的比较排序算法对每个桶内的所有数据进行排序，其时间复杂度为 ∑ O(Ni*logNi) 。其中Ni 为第i个桶的数据量。
很显然，第(2)部分是桶排序性能好坏的决定因素。尽量减少桶内数据的数量是提高效率的唯一办法(因为基于比较排序的最好平均时间复杂度只能达到O(N*logN)了)。因此，我们需要尽量做到下面两点：
(1) 映射函数f(k)能够将N个数据平均的分配到M个桶中，这样每个桶就有[N/M]个数据量。
(2) 尽量的增大桶的数量。极限情况下每个桶只能得到一个数据，这样就完全避开了桶内数据的“比较”排序操作。 当然，做到这一点很不容易，数据量巨大的情况下，f(k)函数会使得桶集合的数量巨大，空间浪费严重。这就是一个时间代价和空间代价的权衡问题了。
对于N个待排数据，M个桶，平均每个桶[N/M]个数据的桶排序平均时间复杂度为：
O(N)+O(M*(N/M)*log(N/M))=O(N+N*(logN-logM))=O(N+N*logN-N*logM)
当N=M时，即极限情况下每个桶只有一个数据时。桶排序的最好效率能够达到O(N).

映射规则为：f(x)=\frac x{10}-c，其中常量位：c=\frac {min}{10}，即以间隔大小 10 来区分不同值域

```c
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
```

