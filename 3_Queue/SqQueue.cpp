#include <stdio.h>
#include <stdlib.h>
#include "SqQueue.h"


void InitQueue(SqQueue *&q){
    q = (SqQueue *)malloc(sizeof(SqQueue));
    q->front = q->rear = 0;  // 设置为队空条件,也就是建立空队
}


void ClearQueue(SqQueue *&q){
    free(q);
}


int QueueEmpty(SqQueue *q){
    return (q->front == q->rear);
}


int enQueue(SqQueue *&q, ElemType e){
    if((q->rear+1)%MaxSize == q->front)  // 进队需要先将队尾指针进行取余进一操作后的结果与队首指针比较, 判断是否队满
        return 0;
    q->rear = (q->rear+1) % MaxSize;  // 进队需要 对 队尾指针进行取余进一操作,以保证队列未满
    q->data[q->rear]=e;
    return 1;
}


int deQueue(SqQueue *&q, ElemType &e){
    if(q->front==q->rear)  // 判断是否队空
        return 0;
    q->front = (q->front+1) % MaxSize;  // 出队需要 对 队首指针进行取余取一操作,以保证队列未空
    e = q->data[q->front];  // 取出出队元素交给e                                                                                           
    return 1;
}


void DispQueue(SqQueue *q){
    ElemType n = 0;
    int index = q->front;
    while(index != q->rear){
        index = (index + 1) % MaxSize;
        n = q->data[index];
        printf("%d ", n);
    }
    printf("\n");
}


void InitQu(QuType *&q){
    q=(QuType *)malloc(sizeof(QuType));
    q->front = 0;
    q->count = 0;
} 


int enQu(QuType *&q, ElemType x){
    int rear;
    if(q->count == MaxSize-1)
        return 0;
    rear = (q->front + q->count) % MaxSize;  //队尾位置
    rear = (rear+1) % MaxSize;  // 队尾位置进1
    q->data[rear] = x;
    q->count++;
    return 1;
}


int DeQu(QuType *&q, ElemType &x){
    if(q->count==0)
        return 0;
    q->front = (q->front+1) % MaxSize;  // 队首位置进1
    x = q->data[q->front];
    q->count--;
    return 1;
}


int QuEmpty(QuType *q){
    return(q->count==0);
}


// 实现队列倒置的算法
int reverse(SqQueue *&q){
    ElemType e;
    if((q->front)%MaxSize != q->rear){
        deQueue(q, e);
        reverse(q);
        enQueue(q, e);

    }
    return 1;
}
