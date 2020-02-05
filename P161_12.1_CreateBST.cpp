#include <stdlib.h>
#include <stdio.h>
#define Infosto "%c "

typedef int KeyType;   //keyword items
typedef char InfoType; //Info items


typedef struct node
{
    KeyType key;
    InfoType data;
    struct node *Lchild, *Rchild;
    struct node *parent;
}BSTNode;

void InsertBST(BSTNode*&bt,KeyType k,InfoType data,BSTNode*root)
//Insert a node with Keyword <k> into BSTree <bt> 
{
    if(bt==NULL)
    {
        bt = (BSTNode *)malloc(sizeof(BSTNode));
        bt->key = k;
        bt->data = data;
        bt->Lchild = bt->Rchild = NULL;
        bt->parent = root;
        return;
    }
    else if(k<=bt->key)
    {
        return InsertBST(bt->Lchild, k,data,bt);
    }
    else
    {
        return InsertBST(bt->Rchild, k,data,bt);
    }
}

BSTNode* CreateBST(KeyType A[],InfoType data[],int n)
//Create a BST from A[0....n-1]
//return BST root pointer
{
    BSTNode *bt = NULL;
    BSTNode *root = NULL;
    for (int i = 0; i < n;i++)
    {
        InsertBST(bt, A[i],data[i],root);
    }
    return bt;
}

void Inorder_tree_walk(BSTNode *bt)
{
    if(bt!=NULL)
    {
        Inorder_tree_walk(bt->Lchild);
        printf(Infosto ,bt->data);
        Inorder_tree_walk(bt->Rchild);
    }
}
void Preorder_tree_walik(BSTNode*bt)
{
    if(bt!=NULL)
    {
        printf(Infosto , bt->data);
        Preorder_tree_walik(bt->Lchild);
        Preorder_tree_walik(bt->Rchild);
    }
}
void Postorder_tree_walk(BSTNode*bt)
{
    if(bt!=NULL)
    {
        Postorder_tree_walk(bt->Lchild);
        Postorder_tree_walk(bt->Rchild);
        printf(Infosto , bt->data);
    }
}

void test1()
{
    BSTNode *bt = NULL;
    KeyType A[10];
    InfoType data[11] = "abcdefghij";
    for (int i = 0; i < 10;i++)
        A[i] = i + 1;
    bt=CreateBST(A, data, 10);
    Inorder_tree_walk(bt);
    printf("\n");
    Postorder_tree_walk(bt);
    printf("\n");
    Preorder_tree_walik(bt);
    printf("\n");
}

/*
int main()
{
    test1();
    system("PAUSE");
    return 0;
}
*/