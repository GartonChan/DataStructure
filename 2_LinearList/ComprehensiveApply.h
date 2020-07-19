#include <stdio.h>
#include <stdlib.h>

// 通过计算任意两张表的简单自然连接过程讨论线性表的应用.
/* 
    笛卡尔积: 两矩阵的各行依次排列组合按照次序排列得到的矩阵 
    i=j : 表示 A表第i列和B表第j列的数据跳出来,相等的组成结果
*/

// 1. 合理存储数据(存储方式)
//  定义单链表,一个结点存储一行.数据域为一个数组->需要定义最大列数

#define MaxCol 10  // 列数必须明确
typedef int ElemType;
typedef struct Node{
    ElemType data[MaxCol];
    struct Node *next;
}Dlist;  // DataList类型(结点类型,一行数据)

// 将行数放于头结点中,因此单独定义头结点类型
typedef struct headNode{
    int Row, Col;  // 记录行数和列数
    Dlist *next;  // 指向Node
}HList;

void create(HList *&h);
void display(HList *h);
void link(HList *h1, HList *h2, HList *&h);