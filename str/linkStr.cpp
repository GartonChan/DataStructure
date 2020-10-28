#include <stdio.h>
#include <stdlib.h>

/*
    链串的组织形式与一般的链表类似.
    而主要的区别在于: 连串一个结点可以存储多个字符.
    通常将链串每个结点所能存储的字符个数称为结点大小.
    结点数据域内不一定总能被字符占满.
    一般而言,结点大小越大,可能的存储密度也越大,而与此同时会导致一些操作不方便.
    因此,存储密度大较适合于静态使用方式,否则应当保持操作灵巧.
*/

// 链串的结点类型定义
typedef struct snode{
    char data;
    struct snode *next;
}LiString;


void StrAssign(LiString *&s, char cstr[]){
    int i;  // 用于扫描字符串常量cstr
    LiString *r, *p; 
    s = (LiString *)malloc(sizeof(LiString));
    r = s;  // 尾插法建立链串s, r始终指向链串s的尾结点
    for(i=0; cstr[i]!='\0'; i++){
        p = (LiString *)malloc(sizeof(LiString));
        p->data = cstr[i];
        r->next = p;
        r = p;  // r的指向后移
    }   
    r->next = NULL;  // 尾结点指向为空
}


void StrCopy(LiString *&s, LiString *t){  // 链串t复制到链串s
    LiString *p = t->next;  // p指向链串t的第一个字符结点
    LiString *q, *r;
    s = (LiString *)malloc(sizeof(LiString));  // 建立链串s头结点,而后经过复制并通过引用返回
    r = s;  // r为新建链串的尾结点.
    while(p!=NULL){  // 用p来遍历t所指向的链串的各个结点
        q = (LiString *)malloc(sizeof(LiString));  // 给链串建立新的结点(s指向的链串)
        q->data = p->data;
        r->next = q;
        r = q;  // 使r保持为尾结点
        p = p->next;  // p的指向后移
    }
    r->next = NULL; 
}


int StrEqual(LiString *s, LiString *t){
    LiString *p = s->next;
    LiString *q = t->next;
    while(p!=NULL && q!=NULL && p->data==q->data){
        p=p->next;
        q=q->next;
    }
    if(p==NULL && q==NULL)
        return 1;
    else
        return 0;
}
