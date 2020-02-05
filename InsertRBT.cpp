#include "Rotation.cpp"
RBTnode *InitNode(KeyType key, InfoType data)
{
    RBTnode *newnode = (RBTnode *)malloc(sizeof(RBTnode));
    newnode->Lchild = newnode->Rchild = NULL;
    newnode->Nil = &Nil;
    newnode->parents = NULL;
    newnode->key = key;
    newnode->data = data;
    newnode->color = red;
    return newnode;
}

void What_s_color(RBTnode*T)
{
    if(T->color==red)
    {
        printf("Red ");
    }
    else
    {
        printf("Black ");
    }
    return;
}

void Preorder_color(RBTnode*T)
{
    if(T!=T->Nil)
    {
        What_s_color(T);
        Preorder_color(T->Lchild);
        Preorder_color(T->Rchild);
    }
}

void Inorder_color(RBTnode*T)
{
    if(T!=T->Nil)
    {
        Inorder_color(T->Lchild);
        What_s_color(T);
        Inorder_color(T->Rchild);
    }
}


void InsertFixupRBT(RBTnode *&T, RBTnode *z)
{
    while (z->parents->color == red)
    {
        if (z->parents == z->parents->parents->Lchild)
        {
            RBTnode *y = z->parents->parents->Rchild;
            if (y->color == red)
            {
                z->parents->color = black;
                y->color = black;
                z->parents->parents->color = red;
                z = z->parents->parents;
            }
            else
            {
                if (z == z->parents->Rchild)
                {
                    z = z->parents;
                    Left_rotate(T, z);
                }
                z->parents->color = black;
                z->parents->parents->color = red;
                Right_rotate(T, z->parents->parents);
            }
        }
        else
        {
            RBTnode *y = z->parents->parents->Lchild;
            if(y->color==red)
            {
                z->parents->color = black;
                y->color = black;
                z->parents->parents->color = red;
                z = z->parents->parents;
            }
            else
            {
                if(z==z->parents->Lchild)
                {
                    z = z->parents;
                    Right_rotate(T, z);
                }
                z->parents->color = black;
                z->parents->parents->color = red;
                Left_rotate(T, z->parents->parents);
            }
            
        }
    }
    T->color = black;
}

void InsertRBT(RBTnode *&T, RBTnode *z)
{
    RBTnode *y = T->Nil;
    RBTnode *x = T;
    while (x != T->Nil)
    {
        y = x;
        if (z->key <= x->key)
        {
            x = x->Lchild;
        }
        else
        {
            x = x->Rchild;
        }
    }
    z->parents = y;
    if (y == T->Nil)
    {
        T = z;
    }
    else if (z->key <= y->key)
    {
        y->Lchild = z;
    }
    else
    {
        y->Rchild = z;
    }
    z->Lchild = &Nil;
    z->Rchild = &Nil;
    z->color = red;
    InsertFixupRBT(T, z);
    //printf("done!\n");
}

void test2()
{
    Nil.color = black;
    Nil.Lchild = Nil.Rchild = Nil.parents = NULL;
    Nil.Nil = &Nil;
    Nil.data = '!';
    RBTnode *T = &Nil;
    InfoType data[4] = "ABC";
    KeyType key[3] = {2, 11, 14};
    for (int i = 0; i < 3;i++)
    {
        RBTnode *newnode = InitNode(key[i], data[i]);
        InsertRBT(T, newnode);
        Preorder(T);
        Preorder_color(T);
        printf("\n");
    }
}

/*
int main()
{
    test2();
    system("PAUSE");
    return 0;
}
*/