/*
    二叉树:
        度为2的树,又称为 二次树或二分树.
        其定义是一种递归定义(应用广泛).  ~要细细品味递归,深入理解递归
            二叉树结构较为简单,存储效率高,运算算法简单,
            并且任何m次树都可以转化为二叉树结构,特别重要!
    
    二叉树的五种形态

    满二叉树
    完全二叉树: 叶子结点依次排列于该层最左边的位置上.
    二叉树的五条重要性质

    存储结构: 1)顺序存储结构  2)链式存储结构
        1) 结点序号 = 下标序号 + 1
            typedef ElemType SqBtree[Maxsize];
        
        2) 由data域和两个孩子结点的指针域 构成一个结点.
            typedef struct node{
                ElemType data;
                struct node *lchild, *rchild;
            }BTNode;

            对非完全二叉树和满二叉树用链式存储结构更方便


    二叉树的基本运算概述

        1. 创建二叉树 CreateBTNODE(*b, *str):
            根据二叉树括号表示法的字符串*str生成对应的链式存储结构.

        2. 查找结点 FindNode(*b, x):
            在二叉树b中寻找data域值为x的结点,并返回指向该结点的指针.

        3. 找孩子结点LchildNode(p)和RchildNode(p):
            分别求二叉树中结点*p的左孩子结点和右孩子结点.

        4. 求高度BTNodeDepth(*b):
            求二叉树b的高度.若二叉树为空,则其高度为0;
            否则,其高度等于左子树 与 右子树中的最大高度加1.

        5. 输出二叉树DispBTNode(*b):
            以括号表示法输出一棵二叉树.


    括号表示法: A(B(D(,G)),C(E,F))
*/

#define MaxSize 30

typedef char ElemType;

typedef ElemType SqBtree[MaxSize];

typedef struct node
{
    ElemType data;
    struct node *lchild, *rchild;
}BTNode;

/*
    二叉树遍历:
        按照一定次序,访问树中所有结点,且每个结点只访问一次.
        是二叉树中所有运算的基础
        按照子树递归调用方法划分成为三种:  
            1.先序遍历: 访问根结点 -> 先序遍历左子树 (-> 新的根结点) -> 先序遍历右子树
            2.中序遍历: 中序遍历(遍历不等同于访问)左子树 -> 访问根结点 -> 中序遍历右子树
            3.后序遍历: 后序遍历左子树 -> 先序遍历右子树 -> 访问根结点
*/


/* -- 二叉树的基本运算 -- */
void CreateBTNode(BTNode *&b, char *str);
// 根据二叉树括号表示法的字符串*str生成对应的链式存储结构
BTNode *FindNode(BTNode *b, ElemType x);  
// 在二叉树b中寻找data域为x的结点,并返回指向该结点的指针
BTNode *LchileNode(BTNode *p);
BTNode *RchildNode(BTNode *p);
int BTNodeDepth(BTNode *b);
// 求二叉树的高度的递归模型
void DispBTNode(BTNode *b);
// 递归处理左右子树


/* -- 二叉树的遍历 -- */
void preOrder(BTNode *b);  // 先序遍历的非递归算法
void inOrder(BTNode *b);  // 中序遍历的非递归算法
void postOrder(BTNode *b);  // 后序遍历的非递归算法
void PreOrder(BTNode *b);  // 先序遍历的递归算法
void InOrder(BTNode *b);  // 中序遍历的递归算法
void PostOrder(BTNode *b);  // 后序遍历的递归算法
void levelOrder(BTNode *b);  // 层次遍历
void DispLeaf(BTNode *b);  // 输出叶子结点
int Like(BTNode *b1, BTNode *b2);  // 判断相似


/* -- 二叉树的沟槽 -- */
BTNode *CreateBTNode1(char *pre, char *in, int n);
// 由先序和中序序列(定理)构造二叉树
BTNode *CreateBTNode2(char *post, char *in, int n);
// 由先序和中序序列(定理)构造二叉树