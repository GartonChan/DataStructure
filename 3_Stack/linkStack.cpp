#include <stdio.h>
#include <stdlib.h>
#include "linkStack.h"


void InitStack(LinkStack *&s){
    s = (LinkStack *)malloc(sizeof(LinkStack));
    s->next = NULL;
}


void ClearStack(LinkStack *&s){
    LinkStack *p;
    while(s != NULL){
        p = s->next;  // 保持链表不被断掉
        free(s);
        s = p;
    }
}


int StackLength(LinkStack *s){
    int i = 0;
    LinkStack *p = s->next;  // 定义p为栈顶指针
    while(p){  // 遍历到栈底
        i++;
        p = p->next;
    }
    return i;
}


int StackEmpty(LinkStack *s){
    return (s->next == NULL);  // 判断栈顶为空的情况
}


void Push(LinkStack *&s, ElemType e){
    LinkStack *p;
    p = (LinkStack *)malloc(sizeof(LinkStack));
    p->data = e;  // 插入数值
    p->next = s->next;  // 新入栈元素成为新的栈顶与原先栈顶建立关联 
    s->next = p;  // 指向链表的指针与栈顶指针建立关联
}


int Pop(LinkStack *&s, ElemType &e){
    LinkStack *p;
    if(s->next == NULL)  // 栈空的情况
        return 0;
    p = s->next;  // p指向栈顶
    e = p->data;  // 取出栈顶数据
    s->next = p->next;  //  将栈顶元素出栈
    free(p);
    return 1;
}


int GetTop(LinkStack *s, ElemType &e){
    if(s->next==NULL)  // 栈空的情况
        return 0;
    e = s->next->data;  // 获得栈顶元素数据
    return 1;
}


void DispStack(LinkStack *s){
    LinkStack *p = s->next;  // p为栈顶指针
    while(p != NULL){  // 扫描从栈顶到栈底,依次打印
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}