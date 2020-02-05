#include "RBTnode.cpp"

void Left_rotate(RBTnode *&T, RBTnode *x)//注意这里x不能用指针的引用(*&),因为在旋转中可能x会和T指向同一个结点,x的操作会直接改变T
{
    RBTnode *y = x->Rchild;
    x->Rchild = y->Lchild;

    if (y->Lchild != T->Nil)
    {
        y->Lchild->parents = x;
    }
    y->parents = x->parents;
    if (x->parents == T->Nil)
    {
        T = y;
    }
    else if (x == x->parents->Lchild)
    {
        x->parents->Lchild = y;
    }
    else
    {
        x->parents->Rchild = y;
    }
    y->Lchild = x;
    x->parents = y;
}

void Right_rotate(RBTnode*T,RBTnode*y)
{
    RBTnode *x = y->Lchild;

    y->Lchild = x->Rchild;
    if(x->Rchild!=T->Nil)
    {
        x->Rchild->parents = y;
    }
    
    x->parents = y->parents;
    if(y->parents==T->Nil)//y is RBT root
    {
        T = x;
    }
    else if(y==y->parents->Rchild)
    {
        y->parents->Rchild = x;
    }
    else
    {
        y->parents->Lchild = x;
    }
    
    x->Rchild = y;
    y->parents = x;
}




void Preorder(RBTnode *T)
{
    if(T!=T->Nil)
    {
        printf("%c ", T->data);
        Preorder(T->Lchild);
        Preorder(T->Rchild);
    }
}

void Inorder(RBTnode *T)
{
    if(T!=T->Nil)
    {
        Inorder(T->Lchild);
        printf("%c ", T->data);
        Inorder(T->Rchild);
    }
}

void test1()
{
    Nil.color = black;
    Nil.Lchild = Nil.Rchild = Nil.parents = NULL;
    Nil.Nil = &Nil;
    Nil.data = '!';
    RBTnode *T = (RBTnode *)malloc(sizeof(RBTnode));
    RBTnode *b = (RBTnode *)malloc(sizeof(RBTnode));
    RBTnode *c = (RBTnode *)malloc(sizeof(RBTnode));
    RBTnode *d = (RBTnode *)malloc(sizeof(RBTnode));
    RBTnode *e = (RBTnode *)malloc(sizeof(RBTnode));

    T->data = 'a';
    b->data = 'b';
    c->data = 'c';
    d->data = 'd';
    e->data = 'e';

    T->parents = &Nil;
    b->parents = T;
    c->parents = T;
    d->parents = c;
    e->parents = c;

    b->Lchild = &Nil;
    b->Rchild = &Nil;
    d->Lchild = &Nil;
    d->Rchild = &Nil;
    e->Lchild = &Nil;
    e->Rchild = &Nil;

    T->Lchild = b;
    T->Rchild = c;
    c->Lchild = d;
    c->Rchild = e;

    T->Nil = &Nil;
    b->Nil = &Nil;
    c->Nil = &Nil;
    d->Nil = &Nil;
    e->Nil = &Nil;

    printf("T=%c \n", T->data);
    Preorder(T);
    printf("\n");

    printf("T=%c \n", T->data);
    Left_rotate(T, T->Rchild);
    Preorder(T);
    printf("\n");

    printf("T=%c \n", T->data);
    Right_rotate(T, T->Rchild);
    Preorder(T);
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