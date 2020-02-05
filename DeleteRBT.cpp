#include "InsertRBT.cpp"
void TransplantRBT(RBTnode*&T,RBTnode*u,RBTnode*v)
{
    if(u->parents==T->Nil)
    {
        T = v;
    }
    else if(u==u->parents->Lchild)
    {
        u->parents->Lchild = v;
    }
    else
    {
        u->parents->Rchild = v;
    }
    v->parents = u->parents;
}

RBTnode*Minimum_RBT(RBTnode*bt)
{
    while(bt->Lchild!=bt->Nil)
    {
        bt = bt->Lchild;
    }
    return bt;
}

RBTnode*SearchRBT(RBTnode*T,KeyType key)
{
    RBTnode *find = T;
    while (find->key!=key)
    {
        if(find->key<key)
            find = find->Rchild;
        else
            find = find->Lchild;
        //printf("find->key=%d\n",find->key);
    }
    return find;
}
void DeleteFixupRBT(RBTnode*&T,RBTnode*x)
{
    while(x!=T&&x->color==black)
    {
        if(x==x->parents->Lchild)
        {
            RBTnode *w = x->parents->Rchild;
            if(w->color==red)
            {
                w->color = black;
                x->parents->color = red;
                Left_rotate(T, x->parents);
                w = x->parents->Rchild;
            }
            if(w->Lchild->color==black&&w->Rchild->color==black)
            {
                w->color = red;
                x = x->parents;
            }
            else
            {
                if(w->Rchild->color==black)
                {
                    w->Lchild->color = black;
                    w->color = red;
                    Right_rotate(T, w);
                    w = x->parents->Rchild;
                }
                w->color = x->parents->color;
                x->parents->color = black;
                w->Rchild->color = black;
                Left_rotate(T, x->parents);
                x = T;
            }
        }
        else if(x==x->parents->Rchild)
        {
            RBTnode *w = x->parents->Lchild;
            if(w->color==red)
            {
                w->color = black;
                x->parents->color = red;
                Right_rotate(T, x->parents);
                w = x->parents->Lchild;
            }
            if(w->Rchild->color==black&&w->Lchild->color==black)
            {
                w->color = red;
                x = x->parents;
            }
            else
            {
                if(w->Lchild->color==black)
                {
                    w->Rchild->color = black;
                    w->color = red;
                    Left_rotate(T, w);
                    w = x->parents->Lchild;
                }
                w->color = x->parents->color;
                x->parents->color = black;
                w->Lchild->color = black;
                Right_rotate(T, x->parents);
                x = T;
            }
        }  
    }
    x->color = black;
}



void DeleteRBT(RBTnode*T,KeyType key)
{
    RBTnode *z = SearchRBT(T, key);
    RBTnode *y = z;
    RBTnode *x = NULL;
    bool y_original_color = y->color;
    if(z->Lchild==T->Nil)
    {
        x = z->Rchild;
        TransplantRBT(T, z, z->Rchild);
    }
    else if(z->Rchild==T->Nil)
    {
        x = z->Lchild;
        TransplantRBT(T, z, z->Lchild);
    }
    else
    {
        y = Minimum_RBT(z->Rchild);
        y_original_color = y->color;
        x = y->Rchild;
        if(y->parents==z)
        {
            x->parents = y;
        }
        else
        {
            TransplantRBT(T, y, y->Rchild);
            y->Rchild = z->Rchild;
            y->Rchild->parents = y;
        }
        TransplantRBT(T, z, y);
        y->Lchild = z->Lchild;
        y->Lchild->parents = y;
        y->color = z->color;
    }
    if(y_original_color==black)
    {
        DeleteFixupRBT(T, x);
    }
}

void test3()
{
    KeyType key[5] = {1, 2, 11, 14, 15};
    char data[6] = "ABCDE";
    Nil.color = black;
    Nil.Lchild = Nil.Rchild = Nil.parents = NULL;
    Nil.Nil = &Nil;
    Nil.data = '!';
    RBTnode *T = &Nil;
    for (int i = 0; i < 5;i++)
    {
        RBTnode *newnode = InitNode(key[i], data[i]);
        InsertRBT(T, newnode);
        Preorder(T);
        Preorder_color(T);
        printf("\n");
        Inorder(T);
        Inorder_color(T);
        printf("\n");
    }
    //TransplantRBT(T, T->Rchild, T->Rchild->Rchild);
    DeleteRBT(T, 15);
    Preorder(T);
    Preorder_color(T);
}

int main()
{
    test3();
    system("PAUSE");
    return 0;
}