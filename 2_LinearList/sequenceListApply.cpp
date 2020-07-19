#include "sequenceList.cpp"


// 将元素x插入到有序线性表中
void Insert(SqList *&L, ElemType x){
    int i=0, j;
    while(i < L->length && L->data[i] < x)
        i++;
    for(j=L->length-1; j>=i; j--){
        L->data[j+1] = L->data[j];
    }
    L->data[i] = x;
    L->length += 1;
}


// 二路归并思想解决两个有序线性表合并在一起的问题
SqList *merge(SqList *p, SqList *q){  
// i, j为位指针 两表中较小者的下标后移，有一表处理完成 剩余元素直接放入新的数据表。
    SqList *r;
    int i = 0, j= 0, k = 0;
    r = (SqList *)malloc(sizeof(SqList));
    while(i < p->length && j < q->length){
        if(p->data[i] < q->data[j]){
            r->data[k] = p -> data[i];
            i++;
            k++;
        }else{
            r->data[k] = q->data[j];
            j++;
            k++;
        }
        while(i<p->length){
            r->data[k] = p->data[i];
            i++;
            k++;
        }
        while(j<q->length){
            r->data[k] = q->data[j];
            j++;
            k++;
        }
        r->length = k;
        return r;
    }
}


/*
已知长度n的线性表A顺序存储结构
要求算法删除线性表中所有值为item的数据元素
要求时间复杂度O(n)， 空间复杂度O(1)
这里有以下的两种算法：
*/

void delnode1(SqList &A, ElemType item){
    int k=0, i;
    for(i=0;i<A.length;i++){
        if(A.data[i]!=item){
            A.data[k] = A.data[i];
            k++;
        }
    }
    A.length = k;
}

void delnode2(SqList &A, ElemType item){
// k统计个数，将其他元素前移覆盖item元素
    int k=0, i=0;
    while(i < A.length){
        if(A.data[i] == item) 
            k++;
        else
            A.data[i-k] = A.data[i];  
            //将不等于item的当前元素 前移k个位置(k是动态的)
        i++;
    }
    A.length = A.length - k;
}


// 删除所有元素在[x, y]之间的所有元素。
void delelem(SqList *&L, ElemType x, ElemType y){
    int i = 0, j = 0;  
    // i用于扫描遍历, j用于记录不符合条件元素个数
    while(i < L->length){
        if(!(L->data[i] >= x && L->data[i <= y])){  //保留项
            L->data[j] = L->data[i];
            j++;
        }
        i++;
    }
    L->length = j;
}


// 假设Elemtype类型的顺序表L所有元素均不相等
// 现设计算法，以第一个元素为分界线，将小于它的移到前面，大于移到后面
void move1(SqList *&L){
    int i=0, j=L->length-1;
    ElemType pivot = L->data[0];  // 以data[0]为基准
    ElemType tmp;
    while(i!=j){  // 区间两端交替向中间扫描，直至i=j为止
        while(j > i && L->data[j] > pivot)
            j--;  // 从右向左找第1个 小于 pivot的元素
        while(i < j && L->data[i] < pivot)
            i++;  // 从左向右找第1个 大于 pivot的元素
        if(i<j){  // L->data[i]和L->data[j]进行交换
            tmp = L->data[i];
            L->data[i] = L->data[j];
            L->data[j] = tmp;
        }
    }
}


void move2(SqList *&L){
    int i = 0, j = L->length-1;
    ElemType pivot = L->data[0];  // 设置基准
    while(i != j){  // 遍历终点
        while(j > i && L->data[j] > pivot)
            j--;
        L->data[i] = L->data[j];
        while(i < j && L->data[i] < pivot)
            i++;
        L->data[j] = L->data[i];
    }
    L->data[i] = pivot;
}


int main(int argc, char const *argv[])
{
    // printf("Main function start\n");
    SqList *listP;
    printf("Define\n");
    char array[10] = {3, 5, 6, 1, 4, 2, 7, 9, 8, 0};
    // printf("Create\n");
    CreateList(listP, array, 10);
    // printf("%d\n" ,ListLength(listP));
    // printf("Disp\n");
    DispList(listP);
    move2(listP);
    DispList(listP);
    return 0;
}

