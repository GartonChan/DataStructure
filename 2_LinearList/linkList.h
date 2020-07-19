typedef char ELemtype;

typedef struct LNode{  // 定义单链表 结点 类型 LinkNode
    ELemtype data;
    struct LNode *next;  // 指向后继结点
}LinkList;

// 需要注意的是 头结点 (只含指针域或者说其实就是个指针)
// 而第一个结点通常带有数据

/*
    结点的作用是使所有链表（包括空表）的头指针非空
    并使对单链表的插入、删除操作不需要区分是否为空表或是否在第一个位置进行
    从而与其他位置的插入、删除操作一致。
*/

// 单链表的建立方法： 头插法建表 和 尾插法建表
// 区别在于 建立链表时,新一元素插入的位置在头还是在尾


void CreateListF(LinkList *&L, ELemtype a[], int n);  // 头插法建表
void CreateListR(LinkList *&L, ELemtype a[], int n);  // 尾插法建表
void InitList(LinkList *&L);
void DestroyList(LinkList *&L);
int ListLength(LinkList *L);
void DispList(LinkList *L);
int GetElem(LinkList *L, int i, ELemtype &e);
int LocateElem(LinkList *L, ELemtype e);
int ListInsert(LinkList *&L, int i, ELemtype e);
int ListDelete(LinkList *&L, int i, ELemtype e);