#include <stdio.h>
#include <stdlib.h>

typedef int KeyType;
typedef char InfoType;
typedef struct node
{
    struct node *Lchild;
    struct node *Rchild;
    struct node *parents;
    KeyType key;
    InfoType data;
}AVLnode;
