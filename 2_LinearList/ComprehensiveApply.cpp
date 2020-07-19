#include <stdio.h>
#include "ComprehensiveApply.h"

int main(int argc, char const *argv[])
{
    HList *h1, *h2, *h;
    create(h1);
    create(h2);
    printf("disp(h1):\n");
    display(h1);
    printf("\ndisp(h2):\n");
    display(h2);
    link(h1, h2, h);
    printf("\ndisp(h):\n");
    display(h);
    return 0;
}

void create(HList *&h){
    int i, j;
    Dlist *s, *r = NULL;  // 尾插法,需要一个尾指针
    h = (HList *)malloc(sizeof(HList));
    h->next = NULL;
    printf("Row, Col:");
    scanf("%d%d",&h->Row, &h->Col);
    for (i=0; i<h->Row; i++){
        printf("第%d行:", i+1);  // 每次输入一行数据
        s = (Dlist *)malloc(sizeof(Dlist));
        for (j=0; j<h->Col; j++){
            scanf("%d", &s->data[j]);
        }
        if (h->next == NULL)  // 特殊处理,头结点为空,说明当前结点为第一个结点
            h->next = s;  // 建立与头结点的联系
        else 
            r->next = s;  // 否则不是起始结点就在尾结点后插入
        r = s; //保持r指向尾结点;
    }
    if (r!=NULL)  // 表不为空的时候,尾结点的指针一定指向为空
        r->next = NULL;
}

void display(HList *h){  // 输出表的算法
    int j;
    Dlist *p = h->next;
    while (p != NULL){  // p不为空时
        for (j=0;j<h->Col; j++)  // 内层循环输出每一行的每一列
            printf("%4d", p->data[j]);
        printf("\n");
        p = p->next;  // 指针后移
    }
}

void link(HList *h1, HList *h2, HList *&h){
    int f1, f2, i;
    Dlist *p = h1->next, *q;  // q可以不初始化的原因是需要多次扫描(每次都初始化),因此没有必要多初始化一次
    Dlist *s, *r = NULL;
    // 自然连接条件的判断: p->data[f1-1] == q->data[f2-1]
    // 成立, 就在新建链表h中添加一个新的结点.
    printf("连接的字段是:第1个表位序,第2个表位序: ");
    scanf("%d%d", &f1, &f2);
    h = (HList *)malloc(sizeof(HList));
    h->Row = 0;
    h->Col = h1->Col + h2->Col;
    h->next = NULL;
    while (p != NULL){  // 最外层循环对表1遍历
        q = h2->next;
        while (q != NULL){  // 内循环对表2遍历
            // printf("%d == %d ?\n", p->data[f1-1], q->data[f2-1]);
            if (p->data[f1-1] == q->data[f2-1]){
                s = (Dlist *)malloc(sizeof(Dlist));  // s指向新建的结点, r指向尾结点
                // 下面两个最内层的for循环分别是复制表1,表2的当前航
                // h->Col <= MaxCol
                for (i=0; i<h1->Col; i++)  // 复制表1当前行
                    s->data[i] = p->data[i];
                for (i=0; i<h2->Col; i++)  // 复制表2当前行
                    s->data[h1->Col+i] = q->data[i];
                // printf("copied one line\n");
                if (h->next == NULL) 
                    h->next = s;   // 对头结点的特殊处理(插入的为起始结点)
                else 
                    r->next = s;  // 不是起始结点则插入到当前尾结点后面.
                r = s;  // r后移保持指向尾结点. 
                h->Row++;  // 表h的行数+1
            }
            q = q->next;  // 表2的指针移动到下一行
        }
        p = p->next;  //  表1的指针移动到下一行
    }
    if (r!=NULL) 
        r->next =NULL;  // 令表的尾结点next域为空
}
