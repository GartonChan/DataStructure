// 链栈
// 由于链表实现,所以没有栈满上溢的问题
// 一端入栈出栈,所以规定所有操作在单链表的表头进行
// 这里,我们将单链表的头结点设为栈顶, 尾结点设为栈底 (相当于在链表中以头插法建表,这里是头插法建栈)

typedef char ElemType;

typedef struct linkNode
{
    ElemType data;
    linkNode *next;
}LinkStack;


void InitStack(LinkStack *&s);
void ClearStack(LinkStack *&s);
int StackLength(LinkStack *s);
int StackEmpty(LinkStack *s);
void Push(LinkStack *&s, ElemType e);
int Pop(LinkStack *&s, ElemType &e);
int GetTop(LinkStack *s, ElemType &e);
void DispStack(LinkStack *s);
