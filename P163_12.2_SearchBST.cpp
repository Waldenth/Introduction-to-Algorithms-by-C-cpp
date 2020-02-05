#include "P161_12.1_CreateBST.cpp"

//Search node whose key is <k> in BST <bt>
//if find success,return node pointer,else return NULL
BSTNode*SearchBST_Recursive(BSTNode*bt,KeyType k)
{
    if(bt==NULL||bt->key==k)
        return bt;
    if(k<bt->key)
        return SearchBST_Recursive(bt->Lchild, k);
    else
        return SearchBST_Recursive(bt->Rchild, k);
}

BSTNode*SearchBST_Inerative(BSTNode*bt,KeyType k)
{
    while(bt!=NULL)
    {
        if(k==bt->key)
            return bt;
        else if(k<bt->key)
            bt = bt->Lchild;
        else
            bt = bt->Rchild;
    }
    return NULL;
}

BSTNode*Minimum_BST(BSTNode*bt)
{
    while(bt->Lchild!=NULL)
    {
        bt = bt->Lchild;
    }
    return bt;
}

BSTNode*Maximum_BST(BSTNode*bt)
{
    while(bt->Rchild!=NULL)
    {
        bt = bt->Rchild;
    }
    return bt;
}

BSTNode*Successor_BST(BSTNode*bt)
{
    if(bt->Rchild!=NULL)
    {
        return Minimum_BST(bt->Rchild);
    }
    BSTNode *tmp = bt->parent;
    while(tmp!=NULL&&bt==tmp->Rchild)
    {
        bt = tmp;
        tmp = tmp->parent;
    }
    return tmp;
}

void Backtracking(BSTNode* node)
{
    while(node!=NULL)
    {
        printf(Infosto, node->data);
        node = node->parent;
    }
}

void test2()
{
    BSTNode *bt = NULL;
    KeyType A[10];
    InfoType data[11] = "abcdefghij";
    for (int i = 0; i < 10;i++)
        A[i] = i + 1;
    bt=CreateBST(A, data, 10);
    Inorder_tree_walk(bt);
    printf("\n");

    BSTNode *target = NULL;
    target=SearchBST_Recursive(bt, 5);
    printf(Infosto,target->data);

    target=SearchBST_Inerative(bt, 5);
    printf(Infosto,target->data);
    printf("\n");

    Backtracking(target);
    printf("\n");

    target = Successor_BST(target);
    printf(Infosto,target->data);
    printf("\n");

    BSTNode *tmp = Minimum_BST(target);
    printf(Infosto, tmp->data);

}


/*
int main()
{
    test2();
    system("PAUSE");
    return 0;
}
*/

