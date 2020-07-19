#include <stdio.h>
#include <stdlib.h>
#include "sequenceList.h"


void CreateList(SqList *&L, ElemType a[], int n){  // L指向顺序表， 数组a存储原始数据
    int i;
    L = (SqList *)malloc(sizeof(SqList));
    for (i = 0; i < n; i++)
    {
        L->data[i] = a[i];
    }
    L->length = n;
}


void InitList(SqList *&L){
    L = (SqList *)malloc(sizeof(SqList));
    L->length = 0;
}


void DestroyList(SqList *&L){
    free(L);
}


int ListEmpty(SqList *&L){
    return (L->length == 0);
}


int ListLength(SqList *L){
    return (L->length);
}


int DispList(SqList *&L){
    int i;
    if(ListEmpty(L))
        return 0;
    for(i = 0; i < L->length; i++)
        printf("%d ", L->data[i]);
    printf("\n");
    return 1;
}


int GetElem(SqList *&L, int i,ElemType &e){
    if(i < 1 || i > L->length)
        return 0;
    e = L->data[i-1];
    return 1;
}


int LocateElem(SqList *&L, ElemType e){
    int i = 0;
    while(i < L->length && L->data[i] != e)
        i++;
    if(i >= L->length)
        return 0;
    else
        return i+1;
}


int ListInsert(SqList *&L, int i, ElemType e){  //插入e 并使其位于第i个的位置上
    int j;
    if(i<1 || i>L->length+1)
        return 0;
    i -= 1;  //逻辑位序换成物理位序
    for(j=L->length-1; j>=i; j--){  //从高位开始逐位往后移一位，要注意的是临界条件
        L->data[j+1] = L->data[j];
    }
    L->data[i] = e;
    L->length += 1;
    return 1;
}


int ListDelete(SqList *&L, int i, ElemType &e){
    int j;
    if(j<1 || j>L->length)
        return 0;
    i -= 1;
    e = L->data[i];
    for (j = i+1; j < L->length; j++)
    {
        L->data[i-1] = L->data[i];
    }
    L->length -= 1;
    return 1;
}

