#include <stdio.h>
#include <stdlib.h>
#define red true
#define black false
typedef int KeyType;
typedef char InfoType;
typedef struct node
{
    bool color;
    KeyType key;
    InfoType data;
    struct node *Lchild;
    struct node *Rchild;
    struct node *parents;
    struct node *Nil;
}RBTnode;

RBTnode Nil;
