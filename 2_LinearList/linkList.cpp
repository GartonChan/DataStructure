#include <stdio.h>
#include <stdlib.h>
#include "linkList.h"


// 头插法建表
void CreateListF(LinkList *&L, ELemtype a[], int n){
    LinkList *s;
    int i;
    L = (LinkList *)malloc(sizeof(LinkList));
    L->next = NULL;
    for(i=0; i<n; i++){
        s = (LinkList *)malloc(sizeof(LinkList));
        s->data = a[i];
        s->next = L->next;  // *s插入至原先开始结点前
        L->next = s;  // *s插入至头结点后
    }
}


// 尾插法建表
void CreateListR(LinkList *&L, ELemtype a[], int n){
    LinkList *s, *r;
    int i;
    L = (LinkList *)malloc(sizeof(LinkList));
    r = L;  // r始终指向尾结点, 开始时指向头结点
    for(i=0; i<n; i++){
        s = (LinkList *)malloc(sizeof(LinkList));
        s->data = a[i];
        r->next = s;
        r = s;
    }
    r->next = NULL;  // 保证r始终指向尾结点,所以尾结点指针值为NULL
}


void InitList(LinkList *&L){
    L = (LinkList *)malloc(sizeof(LinkList));
    L->next = NULL;
}


void DestroyList(LinkList *&L){
    LinkList *p = L, *q = p->next;
    while(q){
        free(p);
        p = q;
        q = p->next;
    }
    free(p);  //此时q为NULL,p指向尾结点,释放最后一个结点
}


int ListLength(LinkList *L){
    LinkList *p = L;  // 定义一个指向头结点的指针 -> 头指针
    int n = 0;
    while(p->next){  // 各个结点的指针域作为判断条件
        n++;  // L(head) -> N1 -> N2 -> N3 -> NULL
        p = p->next;  // 遍历
    }
    return n;
}


void DispList(LinkList *L){
    LinkList *p = L->next;  // 定义一个指向第一个结点的指针
    while(p){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}


int GetElem(LinkList *L, int i, ELemtype &e){
    int j = 0;  // 记录遍历时的索引位置
    LinkList *p = L;  // 从头结点开始,是为了遍历结点的计数正确
    while(j<i && p){
        j++;
        p = p->next;
    }
    if(p == NULL){  // 不存在第i个数据结点
        return 0;
    }
}


int LocateElem(LinkList *L, ELemtype e){
    LinkList *p = L->next;  //指向第1个数据结点
    int i = 1;  //由于p指向的是第一个数据结点,所以i作为索引从1开始
    while(p && p->data != e){  //结束条件为: 在尾结点前找到e或者是到尾结点后都找不到e
        p = p->next;
        i++;
    }
    if(p == NULL){
        return 0;
    }else
    {
        return 1;
    }
}


int ListInsert(LinkList *&L, int i, ELemtype e){
    int j = 0;
    LinkList *p = L, *s;  // p指向头结点
    while (j < i-1 && p)  // 查找第i-1个结点
    {
        j++;
        p = p->next;
    }
    if(p == NULL){
        return 0;
    }else
    {
        s = (LinkList *)malloc(sizeof(LinkList));
        s->data = e;
        s->next = p->next;  // 在第i-1个结点后插入成为第i个结点
        p->next = s;
        return  1;

    }
}


int ListDelete(LinkList *&L, int i, ELemtype e){
    int j = 0;
    LinkList *p = L, *q;
    while(j < i-1 && p){
        j++;
        p = p->next;
    }
    if(p == NULL){
        return 0;
    }else
    {
        q = p->next;  // q指向第i个结点
        if(q == NULL)   // 第i个结点不存在
            return 0;
        e = q->data;
        p->next = q->next;
        free(q);
        return 0;
    }
}