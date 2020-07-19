#define MaxSize 30

typedef char ElemType;
typedef struct 
{
    ElemType data[MaxSize];
    int top;  //栈指针， 伪指针
    // int: 在顺序表中用于记录线性表的长度   
    // 在这里用来记录 栈顶 的索引位置(index), 因此作为栈指针使用
    // 根据它来进行入栈出栈
}SqStack;

// 顺序栈为空的时候  top指针的值可以是n或者0  看具体定义和规则而定
// 栈的实现方式有 自上而下 和 自下而上 建栈

void InitStack(SqStack *&s);
void ClearStack(SqStack *&s);
int StackLength(SqStack *s);
int StackEmpty(SqStack *s);
int Push(SqStack *&s, ElemType e);
int Pop(SqStack *&s, ElemType &e);
int GetTop(SqStack *s, ElemType &e);
void DispStack(SqStack *s);
