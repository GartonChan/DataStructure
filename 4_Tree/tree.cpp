#include <stdio.h>
#include <stdlib.h>
#include "tree.h"


/*  -- 二叉树的基本运算 -- */

// 把用括号表示法表示的二叉树字符串, 用链式存储方式建立起来.
// 难点在于解析字符,尤其是对 ‘(’  ‘,’  ‘)’ 这三个字符的解析
void CreateBTNode(BTNode *&b, char *str){
    // 栈:遍历树和图中处理关系的时候常用的方法
    BTNode *St[MaxSize];  // 栈St用于创建二叉树时保存双亲结点
    BTNode *p = NULL;  // 初始化为空, 在while循环中会不断让p指向新建结点.
    int top = -1;  // 栈St的栈顶指针.
    int k;  // k用于记录是双亲结点的左孩子还是右孩子结点, 1->lchild  2->rchild
    int index = 0;  // index用于记录扫描字符的下标位置.

    char ch;
    ch = str[index];  // 第一次读取字符.
    b = NULL;  // 二叉树的指针b初始化为空.
    while(ch != '\0'){
        switch (ch)  // ch = str[index] 
        {
        case '(':  // "("表示上一个新建的结点有孩子结点(并且首先考虑的是左孩子结点),所以上一个结点进栈
        // 让前面刚创建好的结点进栈作为下一个新建结点的双亲结点.
        // 先令k=1,下一结点为双亲结点的左孩子结点.
        // 后面遇到"," 再令k=2,下一结点为双亲结点的右孩子结点.
            top++;
            St[top] = p;  
            k = 1;  // 左孩子结点标志.
            break;
        case ',':  // 表示其后创建的结点是右孩子结点.
            k = 2;  // 右孩子结点标志.
            break;
        case ')':  // ")"表示栈中栈顶结点的左右孩子结点处理完毕.  
        // 退栈, 回退到上一个双亲结点看有无右孩子结点的情况 
            top--;
            break;    
        default:  // 其他字符时，为创建结点的数据域内容
            p=(BTNode *)malloc(sizeof(BTNode));  // 新开辟内存空间以创建新的结点, p指向新的结点
            p->data = ch;
            p->lchild = p->rchild = NULL;  //.初始化
            if(b == NULL)  // 形参b指向根结点
            // 若b为空, 则将让它指向新结点(新结点成为根结点)
                b = p;
            else{  
            // 否则就由k值决定新建结点是当前双亲结点的左孩子结点还是右孩子结点
                switch (k)
                {
                case 1:
                    St[top]->lchild = p;
                    break;
                case 2:
                    St[top]->rchild = p;
                    break;
                }
            }
        }
        index++;
        ch = str[index];   
    }
}


BTNode *LchildNode(BTNode *p){
    return p->lchild;
}


BTNode *RchildNode(BTNode *p){
    return p->rchild;
}

// 可以通过二叉树的FindNode理解递归的内涵和灵巧
BTNode *FindNode(BTNode *b, ElemType x){
// 采用先序遍历递归算法来查找值为x的结点并返回其指针(失败为NULL)
    BTNode *p;
    if(b==NULL)  // 树为空的情况
        return NULL;
    else if(b->data == x){  // 当前结点作为根结点，其值域就为x，就返回当前结点
        return b;
    }else{  // 一般情况
        p=FindNode(b->lchild, x);  // 开始套娃。
        if(p != NULL){  // 不断遍历左子树直至为空，再遍历其右子树
            return p;   // 当前结点的左孩子结点为空时，再看当前结点的右孩子结点 
        }else{
            return FindNode(b->rchild, x);
        }
    }
}

int BTNodeDepth(node *b){  // ??? 
    int lchildDep, rchildDep;
    if(b==NULL)
        return 0;
    else{
        lchildDep = BTNodeDepth(b->lchild);
        rchildDep = BTNodeDepth(b->rchild);
        return(lchildDep>rchildDep? lchildDep+1: rchildDep+1);
    }
}


void DispBTNode(BTNode *b){  // 打印输出二叉树字符串
    if(b!=NULL){  // 空则不输出
        printf("%c", b->data);
        if(b->lchild!=NULL || b->rchild!=NULL){
            printf("(");
            DispBTNode(b->lchild);  // 递归处理左子树
            if(b->rchild!=NULL)  
                printf(",");
            DispBTNode(b->rchild);  // 递归处理右子树
            printf(")");
        }
    }
}


/* -- 二叉树的遍历 -- */
void PreOrder(BTNode *b){
    if(b != NULL){
        printf("%c", b->data);
        PreOrder(b->lchild);
        PreOrder(b->rchild);
    }
}


void InOrder(BTNode *b){
    if(b != NULL){
        InOrder(b->lchild);
        printf("%c", b->data);
        InOrder(b->rchild);
    }
}


void PostOrder(BTNode *b){
    if(b != NULL){
        PostOrder(b->lchild);
        PostOrder(b->rchild);
        printf("%c", b->data);
    }
}


void preOrder(BTNode *b){
    if(b != NULL){
        BTNode *p;
        BTNode *st[MaxSize];
        int top = -1;
        
        top++;  // 将根结点入栈
        st[top] = b;
        while(top > -1){
            p = st[top];  // 根节点出栈并访问
            top--;
            printf("%c", p->data);
            if(p->rchild){  // 根据栈的特点，右孩子结点先进栈
                top++;
                st[top] = p->rchild;
            }
            if(p->lchild){  // 然后再让左孩子结点进栈（下次循环出栈作为新的根结点访问）
                top++;
                st[top] = p->lchild;
            }
        }
    }
}


void inOrder(BTNode *b){
    if(b != NULL){ 
        BTNode *p = b;
        BTNode *st[MaxSize];
        int top = -1;
        while(top>-1 || p!=NULL){
            while(p!=NULL){
                top++;
                st[top] = p;
                p = p->lchild;
            }  // 扫描所有左结点，进栈并且先出栈的是最左下结点
            if(top > -1){
                p = st[top];
                top--;
                printf("%c", p->data);  
                // 访问最左下结点
                p = p->rchild;
                // 将最左下结点作为新根结点，根据中序遍历原则
                // 令p为右孩子结点，下次循环再扫描其所有左结点
                // 若p已经是叶子结点，则在下次循环会被访问。
            } 
        }
    }
}


// void postOrder(BTNode *b){  // !!!!!!
//     if (b != NULL){
//         BTNode *p;
//         BTNode *st[MaxSize];
//         int top = -1;
//         p = b;
//         while(top > -1 || p != NULL){
//             while(p != NULL){
//                 top++;
//                 st[top] = p;
//                 p->lchild;
//             }  // 扫描
//             if(top >-1){
//                 p = st[top];
//                 top--;
//                 printf("%c", p->data);
//                 p->rchild;
//             }
//         }

//     }
// }


void levelOrder(BTNode *b){
    if (b == NULL)
        printf("err\n");
    else{
        BTNode *p;
        BTNode *qu[MaxSize];  // 用队列先进先出的特性存储即将遍历的结点.
        int front;
        int rear;
        front = rear = -1; // init
        rear++;
        qu[rear] = b;
        while (front != rear){
            front = (front + 1) % MaxSize;
            p = qu[front];  // 队头出队列
            printf("%c", p->data);  // 访问出队列的队头结点
            if (p->lchild != NULL){
                rear = (rear + 1) % MaxSize;
                qu[rear] = p->lchild;
            }
            if (p->rchild != NULL){
                rear = (rear + 1) % MaxSize;
                qu[rear] = p->rchild;
            }
        }
    }
}

void DispLeaf(BTNode *b){
    if (b!=NULL){
        if(b->lchild || b->rchild){  // 不为叶子结点时往下遍历
            DispLeaf(b->lchild);
            DispLeaf(b->rchild);
        }
        else
            printf("%c", b->data);
    }
}

// 判断相似, 相似返回1，否则返回0

int Like(BTNode *b1, BTNode *b2){
/*
    对相似的判定： 二叉树t1 t2相似
        1. t1 和 t2 都是空树
        2. t1 和 t2 根结点相似，并且各自的左右子树也相似
        相似指的是 具有的结构相同
*/
    int like1, like2;
    if (b1 == NULL && b2 == NULL)
        return 1;  // b1、b2都为空
    else if (b1 == NULL || b2 == NULL)
        return 0;  // b1、b2其中一个为空
    else{  // 都不为空
        like1 = Like(b1->lchild, b2->lchild);
        like2 = Like(b1->rchild, b2->rchild);
        // 递归遍历判断左右子树的结构是否相似
        return (like1 && like2);  // 都相似才(相似)返回1，否则返回0
    }
}



/* -- 二叉树的构造 -- */

// 从这个 构造二叉树 的算法,可以增进对二叉树递归定义的理解.(对递归的理解)
BTNode *CreateBTNode1(char *pre, char *in, int n){
    BTNode *s;
    char *p;
    int k;
    if (n <= 0)
        return NULL;
    s = (BTNode *)malloc(sizeof(BTNode));  // 新建结点*s, 定义根
    s->data = *pre;
    for (p = in; p < in+n; p++)  // 根找到了,就在中序中找根的位置k
        if (*p == *pre)
            break;  // 跳出循环后p的位置就是in中根结点所在的位置
    k = p-in;  // k为根在中序的位置(下标)
    // 随后划分左右子树,得到左前序 右前序 左中序 右中序.  ->  对这样的步骤进行递归,如下:
    s->lchild = CreateBTNode1(pre+1, in, k);  // 递归构造左子树
    s->rchild = CreateBTNode1(pre+k+1, p+1, n-k-1);  // 递归构造右子树
    // 参数里的+1 和-1是考虑到根结点在中间,不能将其算在内
    return s;
}


BTNode *CreateBTNode2(char *post, char *in, int n){
    BTNode *s;
    char *p, r;
    int k;
    if (n <= 0)
        return NULL;
    r = *(post+n-1);  // 后序中最后一个字符:根结点
    s = (BTNode *)malloc(sizeof(BTNode));
    s->data = r;  // 也可以不用r 直接*(post+n+1)表示, 但这样可读性较差.
    for (p=in; p < in+n; p++)
        if (*p == r)
            break;
    k = p-in;
    s->lchild = CreateBTNode2(post, in, k);  
    // 两个序列中的下标从0开始, 所以这里的长度为k而不是k-1
    // a0 a1 ... ak-1 ak ak+1 ... an-1   |   b0 b1 ... bk-1 bk bk+1 ... bn-1
    s->rchild = CreateBTNode2(post+k, p+1, n-k-1);  // 参数里的-1是考虑到根结点在中间,不能将其算在内
    return s;
}


int main(int argc, char const *argv[])
{
    /* -- 二叉树的基本运算 -- */
    printf("/* -- 二叉树的基本运算 -- */\n");
    BTNode *b, *b1, *b2;
    CreateBTNode(b, "A(B(D(,G)),C(E,F))");
    DispBTNode(b);
    printf("\n");
    CreateBTNode(b1, "A(B(D(,G)),C(E,F))");
    DispBTNode(b1);
    printf("\n");
    BTNode *find = FindNode(b, 'C');
    printf("FindNode:%c\n", find->data);


    /* -- 二叉树的遍历 -- */
    printf("/* -- 二叉树的遍历 -- */\n");
    PreOrder(b);
    printf("\n");
    preOrder(b);
    printf("\n");

    InOrder(b);
    printf("\n");
    inOrder(b);
    printf("\n");

    PostOrder(b);
    printf("\n");
    // postOrder(b);  // !!
    // printf("\n");

    levelOrder(b);
    printf("\n");

    DispLeaf(b);
    printf("\n");


    /* -- 二叉树的构造 -- */
    printf("/* -- 二叉树的构造 -- */\n");
    ElemType pre[] = "ABDGCEF", in[] = "DGBAECF", post[] = "GDBEFCA";
    b1 = CreateBTNode1(pre, in, 7);
    printf("b1:");
    DispBTNode(b1);
    printf("\n");
    b2 = CreateBTNode2(post, in, 7);
    printf("b2:");
    DispBTNode(b2);
    printf("\n");
    return 0;
}
