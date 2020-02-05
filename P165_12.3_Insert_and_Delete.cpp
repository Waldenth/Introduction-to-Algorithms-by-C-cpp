#include "P163_12.2_SearchBST.cpp"
//<InsertBST()> in CreateBST.cpp

//replace <u>root subtree with <v>root subtree
void Transplant(BSTNode*&bt,BSTNode*u,BSTNode*v)
{
  if(u->parent==NULL)// u is the root of BST
  {
      bt = u;
  }
  else if(u==u->parent->Lchild)
  {
      u->parent->Lchild = v;
  }
  else
  {
      u->parent->Rchild = v;
  }
  if(v!=NULL)
      v->parent = u->parent;
  return;
}

void DeleteBST(BSTNode*&bt,KeyType k)
{
    BSTNode *target = SearchBST_Inerative(bt, k);
    if (target->Lchild == NULL) //target node doesnt have Leftchild
    {
        Transplant(bt, target, target->Rchild);
    }
    else if(target->Rchild==NULL)
    {
        Transplant(bt, target, target->Lchild);
    }
    else
    {
        BSTNode *tmp = Minimum_BST(target->Rchild);//tmp NOT have Leftchild
        if(tmp->parent!=target)
        {
            Transplant(bt, tmp, tmp->Rchild);
            tmp->Rchild = target->Rchild;
            tmp->Rchild->parent = tmp;
        }
        Transplant(bt, target, tmp);
        tmp->Lchild = target->Lchild;
        tmp->Lchild->parent = tmp;
    }
    return;
}

void test3()
{
    BSTNode *bt = NULL;
    KeyType A[10];
    InfoType data[11] = "abcdefghij";
    for (int i = 0; i < 10;i++)
        A[i] = i + 1;
    bt=CreateBST(A, data, 10);
    Inorder_tree_walk(bt);
    printf("\n");

    DeleteBST(bt, 3);
    Inorder_tree_walk(bt);
    printf("\n");

}



int main()
{
    test3();
    system("PAUSE");
    return 0;
}


