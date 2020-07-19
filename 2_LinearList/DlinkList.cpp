typedef char ElemType;

typedef struct DNode
{
    ElemType data;
    DNode *prior;
    DNode *next;
}DLinkList;

/*
    插入和删除 
    做图辅助理解
    p为插入和删除处的前一位置
    
    插入s指向的结点时 
        先让s连上后继结点  s->next = p->next;
                        p->next->prior = s;
        再让s连上前驱结点  s->prior = p;
                        p->next = s;  
        // 最终才改变p指向结点的next

    删除q指向的结点时
        先断开p与q的连接而与q的下一结点相连
            p->next = p->next->next; 或 p->next = q->next;
        再断开q的下一结点的前驱连接
            q->next->prior=p;
        再释放q即可

    重点是明确指针域的关系
*/


// 判断双向循环链表的数据是否对称分布
int Equal(DLinkList *L){
    int same=1;
    DLinkList *p = L->next;
    DLinkList *q = L->prior;
    while ((p && same==1))
    {
        if(p->data != q->data)
            same = 0;
        else
        {
            if(p==q) break;  // 数据结点为奇数个的情况
            q = q->prior;
            if(p==q) break;  // 数据结点为偶数个的情况
            p = p->next;
        }
    }
    return same;
}