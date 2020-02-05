#include "AVLnode.cpp"

AVLnode *InitAVLNode(KeyType key, InfoType data)
{
    AVLnode *newnode = (AVLnode *)malloc(sizeof(AVLnode));
    newnode->data = data;
    newnode->key = key;
    newnode->Lchild = NULL;
    newnode->Rchild = NULL;
    newnode->parents = NULL;
    return newnode;
}

void Preorder(AVLnode *T)
{
    if (T != NULL)
    {
        printf("%c ", T->data);
        Preorder(T->Lchild);
        Preorder(T->Rchild);
    }
}

void Inorder(AVLnode *T)
{
    if (T != NULL)
    {
        Inorder(T->Lchild);
        printf("%c ", T->data);
        Inorder(T->Rchild);
    }
}

int AVLHeight(AVLnode *T)
{
    int LchildH, RchildH;
    if (T == NULL)
        return 0;
    else
    {
        LchildH = AVLHeight(T->Lchild);
        RchildH = AVLHeight(T->Rchild);
        return (LchildH > RchildH) ? (LchildH + 1) : (RchildH + 1);
    }
}

bool IsBalanceNode(AVLnode *node)
{
    int LchildH = AVLHeight(node->Lchild);
    int RchildH = AVLHeight(node->Rchild);
    int deltaH = LchildH - RchildH;
    if (deltaH >= -1 && deltaH <= 1)
        return true;
    else
        return false;
}

bool IsInsubtree(AVLnode *root, AVLnode *target)
{
    if (root == NULL)
        return false;
    else
    {
        if (root == target)
            return true;
        else
        {
            bool Lsub = IsInsubtree(root->Lchild, target);
            bool Rsub = IsInsubtree(root->Rchild, target);
            return (Lsub || Rsub);
        }
    }
}

int JudgeState(AVLnode *T, AVLnode *Insertnode)
{
    if (T->Lchild != NULL)
    {
        bool LL = IsInsubtree(T->Lchild->Lchild, Insertnode); //case 1
        if (LL)
            return 1;
    }
    if (T->Rchild != NULL)
    {
        bool RR = IsInsubtree(T->Rchild->Rchild, Insertnode); //case 2
        if (RR)
            return 2;
    }
    if (T->Lchild != NULL)
    {
        bool LR = IsInsubtree(T->Lchild->Rchild, Insertnode); //case 3
        if (LR)
            return 3;
    }
    if (T->Rchild != NULL)
    {
        bool RL = IsInsubtree(T->Rchild->Lchild, Insertnode); //case 4
        if (RL)
            return 4;
    }
    return 0;
}

void AdjustLL(AVLnode*&T,AVLnode *A)
{
    AVLnode *B = A->Lchild;

    A->Lchild = B->Rchild;
    if(B->Rchild!=NULL)
        B->Rchild->parents = A;

    B->parents = A->parents;
    if(A->parents!=NULL)
    {
        if(A->parents->Lchild==A)
            A->parents->Lchild = B;
        else
            A->parents->Rchild = B;
    }
    B->Rchild = A;
    A->parents = B;
    if(A==T)
    {
        T = B;
    }
}
void AdjustRR(AVLnode*&T,AVLnode *A)
{
    AVLnode *B = A->Rchild;

    A->Rchild = B->Lchild;
    if(B->Lchild!=NULL)
        B->Lchild->parents = A;

    B->parents = A->parents;
    if(A->parents!=NULL)
    {
        if(A->parents->Rchild==A)
            A->parents->Rchild = B;
        else
            A->parents->Lchild = B;
    }
    B->Lchild = A;
    A->parents = B;
    if(A==T)
    {
        T = B;
    }
}
void AdjustLR(AVLnode*&T,AVLnode *A)
{
    AVLnode *B = A->Lchild;
    AVLnode *C = B->Rchild;

    B->Rchild = C->Lchild;
    C->Lchild->parents = B;

    A->Lchild = C->Rchild;
    if(C->Rchild!=NULL)
        C->Rchild->parents = A;

    C->parents = A->parents;
    if(A->parents!=NULL)
    {
        if(A->parents->Lchild==A)
            A->parents->Lchild = C;
        else
            A->parents->Rchild = C;
    }

    C->Lchild = B;
    B->parents = C;

    C->Rchild = A;
    A->parents = C;
    if(A==T)
    {
        T = C;
    }
}
void AdjustRL(AVLnode*&T,AVLnode *A)
{
    AVLnode *B = A->Rchild;
    AVLnode *C = B->Lchild;

    B->Lchild = C->Rchild;
    C->Rchild->parents = B;

    A->Rchild = C->Lchild;
    if(C->Lchild!=NULL)
        C->Lchild->parents = A;

    C->parents = A->parents;
    if(A->parents!=NULL)
    {
        if(A->parents->Lchild==A)
            A->parents->Lchild = C;
        else
            A->parents->Rchild = C;
    }

    C->Lchild = A;
    A->parents = C;

    C->Rchild = B;
    B->parents = C;
    if(A==T)
    {
        T = C;
    }
}

void FixupAVL(AVLnode *&T, AVLnode *Insertnode)
{
    AVLnode *backtrack = Insertnode->parents;
    while (backtrack != NULL)
    {
        if (IsBalanceNode(backtrack))
        {
            backtrack = backtrack->parents;
            continue;
        }
        else
        {
            int state = JudgeState(backtrack, Insertnode);
            switch (state)
            {
            case 1:
                AdjustLL(T,backtrack);
                //printf("LL\n");
                break;
            case 2:
                AdjustRR(T,backtrack);
                //printf("RR\n");
                break;
            case 3:
                AdjustLR(T,backtrack);
                //printf("LR\n");
                break;
            case 4:
                AdjustRL(T,backtrack);
                //printf("RL\n");
                break;
            default:
                printf("error,No Subtree Found\n");
                system("PAUSE");
                break;
            }
            break;
        }
    }
}

void InsertAVL(AVLnode *&T, AVLnode *newnode)
{
    if (T == NULL)
    {
        T = newnode;
        return;
    }
    else
    {
        AVLnode *pointer = T;
        AVLnode *location = NULL;
        while (pointer != NULL)
        {
            location = pointer;
            if (newnode->key > pointer->key)
            {
                pointer = pointer->Rchild;
            }
            else
            {
                pointer = pointer->Lchild;
            }
        }
        pointer = NULL;
        if (newnode->key > location->key)
        {
            location->Rchild = newnode;
            newnode->parents = location;
        }
        else
        {
            location->Lchild = newnode;
            newnode->parents = location;
        }
        FixupAVL(T, newnode);
        return;
    }
}

AVLnode*CreateAVL(KeyType key[],InfoType data[],int n)
{
    AVLnode *T = NULL;
    for (int i = 0; i < n; i++)
    {
        AVLnode *newnode = InitAVLNode(key[i], data[i]);
        InsertAVL(T, newnode);
    }
    return T;
}



void test1()
{
    KeyType key[6] = {1,2,3,5,6,4};
    InfoType data[7] = "ABCDEF";
    AVLnode *T = NULL;
    for (int i = 0; i < 6; i++)
    {
        AVLnode *newnode = InitAVLNode(key[i], data[i]);
        InsertAVL(T, newnode);
        Preorder(T);
        printf("\n");
        Inorder(T);
        printf("\n");
    }
}

int main()
{
    test1();
    KeyType key[6] = {1,2,3,5,6,4};
    InfoType data[7] = "ABCDEF";
    AVLnode *T = CreateAVL(key, data, 6);
    Preorder(T);
    system("PAUSE");
    return 0;
}