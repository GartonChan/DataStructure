#include <stdlib.h>
#include <stdio.h>
#include "LinkQueue.h"

void InitQueue(LiQueue *&q){
    q=(LiQueue *)malloc(sizeof(LiQueue));
    q->front = q->rear = NULL;
} 


void ClearQueue(LiQueue *&q){
    QNode *p = q->front, *r;
    while(p!=NULL){
        r = p->next;
        free(p);  //释放数据结点所占用的空间
        p = r;
    }
    free(q);  // 释放链队头结点所占用的空间
}


int QueueEmpty(LiQueue *q){
    return (q->rear == NULL);
}


void enQueue(LiQueue *&q, ElemType e){
    QNode *s;
    s = (QNode *)malloc(sizeof(QNode));  // 这两步建立一个新的数据结点, 并为其开辟内存空间
    s->data = e;
    s->next = NULL;  // 尾插法插入到原先rear->next的位置,s的下一结点一定是NULL
    if(q->rear==NULL){  // 若原队列为空, 新结点既是队首又是队尾结点
        q->front = q->rear = s;
    }else{
        q->rear->next = s; // 同尾插法建表
        q->rear = s;  // 或 q->reat = q->rear->next;
    }
}


int deQueue(LiQueue *&q, ElemType &e){
    /*    三种情况分析    */
    QNode *t;
    if(q->rear==NULL)  // 队列为空
        return 0;
    t = q->front;  // t指向队首结点, 一会用于断出去
    e = t->data;
    if(q->front == q->rear){  // 2.只有一个数据结点
        q->front = q->rear = NULL;
    }else{  // 3.超过一个数据结点
        q->front = t->next;  // 断出t指向的队首结点
    }
    free(t);
    return 1;
}