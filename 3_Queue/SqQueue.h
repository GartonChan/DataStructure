#define MaxSize 20

typedef char ElemType;

typedef struct 
{
    ElemType data[MaxSize];  // 元素个数不超过整数MaxSize
    int front, rear;  // 定义了头指针和位指针, 同顺序栈的top一样都是伪指针
}SqQueue;

void InitQueue(SqQueue *&q);
void ClearQueue(SqQueue *&q);
int QueueEmpty(SqQueue *q);
int enQueue(SqQueue *&q, ElemType e);
int deQueue(SqQueue *&q, ElemType &e);
void DispQueue(SqQueue *q);
int reverse(SqQueue *&q);

/*
Notes:
    队尾指针是rear,队头是front，其中MaxSize为循环队列的最大长度   
    1.队空条件：rear==front   
    2.队满条件：(rear+1) %MaxSize==front   
    3.计算队列长度：(rear-front+MaxSize)%MaxSize   
    4.入队：(rear+1)%MaxSize   
    5.出队：(front+1)%MaxSize
*/

// 已知队首元素位置和队列中元素个数后 可计算得队尾指针
// 以此方式实现队列和队列的基本运算
typedef struct
{
    ElemType data[MaxSize];
    int front;
    int count;
}QuType;
// 队空 count == 0
// 队满 count == MaxSize-1
// rear = (front+count) % MaxSize

void InitQu(QuType *&q);
int enQu(QuType *&q, ElemType x);
int DeQu(QuType *&q, ElemType &x);
int QuEmpty(QuType *q);
