#include <stdio.h>
#include <stdlib.h>
#include "long_integer.h"

int main(int argc, char const *argv[])
{
    Head *h1, *h2;
    h1 = create();
    h2 = create();
    init(h1);
    init(h2);
    // insert_node(head, 1234);
    // insert_node(head, 6789);
    input_long_integer(h1);
    input_long_integer(h2);
    disp_long_integer(h1);
    disp_long_integer(h2);
    add(h1, h2);
    return 0;
}

Head *create()
{
    Head *h;
    h = (Head *)malloc(sizeof(Head));
    return h;
}

void init(Head *h)
{
    h->sign = 0;
    h->node_num = 0;
    h->next = NULL;
    h->rear = NULL;
}

void insert_node_head(Head *h, int data)  // 头插法建表, 使得低位靠近头结点,高位靠近尾结点,方便做运算.  最高位产生进位时可以尾插法进行插入新的结点
{
    Node *p;
    p = (Node *)malloc(sizeof(Node));
    if(h->next == NULL){  // 插入的为头结点时
        p->next = NULL;
        p->prior = NULL;
        h->next = p;
        h->rear = p;      // 尾结点位置
    }else{                // 其他结点
        p->prior = NULL;
        h->next->prior = p;
        p->next = h->next;
        h->next = p;   // 最后修改头结点指向的结点
    }
    p->data = data;
}

void insert_node_rear(Head *h, int data)  // 尾插法建表，用于两个长整数不等长运算的时候
{

}

Node *find_last(Head *h)
{
    Node *p = h->next;  // p 从头结点开始遍历 往后扫描直至p指向尾结点 将其返回
    while(p->next)
        p = p->next;
    h->rear = p;
    return p;
}

void disp_long_integer(Head *h)
{
    Node *p = h->rear;  // 尾结点存放的是最高位的4位数
    while(p){
        if(p->next!=NULL)
            printf(",");
        printf("%d", p->data);
        p = p->prior;
    }
    printf("\n");
}

void input_long_integer(Head *h)
{
    int data = 0;
    char ch = ',';
    printf("Enter a long integer: ");
    while(ch == ','){
        scanf("%d%c", &data, &ch);
        insert_node(h, data);
    }
}

int judge_sign(Head *h)
{
    if((h->rear)->data < 0)  // 找到存储最高位的尾结点,由其数据域判断符号
        h->sign = -1;
    else
        h->sign = 1;
    return h->sign;
}

Head *add(Head *h1, Head *h2)
{
    Head *outcome;
    Node *p1, *p2;
    p1 = find_last(h1);  // p1, p2分别指向h1, h2链表的开始结点（由低位向高位逐位计算，但需要注意的是后面需要用尾插法建表）
    p2 = find_last(h2);
    outcome = create();
    init(outcome);    
    if (judge_sign(h1) == judge_sign(h2)){  // 同号 最简单的情况
        while(p1 && p2){
            insert_node(outcome, (p1->data + p2->data));
            p1 = p1->prior;
            p2 = p2->prior;
        }
        while(p1){
            insert_node(outcome, p1->data);
            p1 = p1->prior;
        }
        while(p2){
            insert_node(outcome, p2->data);
            p2 = p2->prior;
        }
    }
    else{
        
    }
    disp_long_integer(outcome);
    return outcome;
}

Head *sub(Head *h1, Head *h2)  // 默认h1 比 h2 要长, 否则调换二者
{
   Head *outcome;
    outcome = create();
    init(outcome);
   return outcome;
}