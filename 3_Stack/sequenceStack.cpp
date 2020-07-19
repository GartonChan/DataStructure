#include <stdio.h>
#include <stdlib.h>
#include "sequenceStack.h"


void InitStack(SqStack *&s){
    s = (SqStack *)malloc(sizeof(SqStack));
    s->top = -1; // 表明空栈
}


void ClearStack(SqStack *&s){
    free(s);
}


int StackLength(SqStack *s){
    return (s->top+1);  // s->top 相当于(栈顶指针的)物理地址,  而逻辑地址需要+1
}


int StackEmpty(SqStack *s){
    return (s->top == -1);
}


int Push(SqStack *&s, ElemType e){
    if(s->top == MaxSize - 1)  // 栈满的情况
        return 0;
    else
    {
            s->top++;
            s->data[s->top] = e;
            return 1;
    }
    
}


int Pop(SqStack *&s, ElemType &e){
    if(s->top == -1)  // 栈空的情况
        return 0;
    else{
        e = s->data[s->top];
        s->top --;
        return 1;
    }
}


int GetTop(SqStack *s, ElemType &e){
    if(s->top == -1)
        return 0;
    e = s->data[s->top];
    return 1;
}


void DispStack(SqStack *s){
    int i;
    for(i=s->top; i>=0; i--){  // top为-1时标志着空栈 所以循环至0停止
        printf("%d ", s->data[i]);
    }
    printf("\n");
}
