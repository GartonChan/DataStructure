/*
    链队组成:
        1.存储队列元素的单链表
        2.指向队首和队尾指针的链队头结点
*/

typedef char ElemType;

typedef struct qnode
{
    ElemType data;  // 数据元素
    struct qnode *next;
}QNode;
// 借助单链表来存储队列元素

typedef struct{
    QNode *front;  // 指向单链表队头结点
    QNode *rear;  // 指向单链表队尾结点
}LiQueue;
// 借助链表的头结点来存储队首和队尾结点的指针

/*
    头结点两个指针分别指向队首和队尾
    入队: 尾插法插入单链表后,并将队尾指针后移即可
    出队: 注意出栈后头结点的队首结点要指向开始结点的下一结点
    队空时:
    队满时:
*/

void InitQueue(LiQueue *&q);
void ClearQueue(LiQueue *&q);
int QueueEmpty(LiQueue *q);
void enQueue(LiQueue *&q, ElemType e);
int deQueue(LiQueue *&q, ElemType &e);
