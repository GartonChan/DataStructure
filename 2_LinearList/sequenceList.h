
// Ordered Storage

/*

    假设元素类型为ElemType
    Storage Used: n * sizeof(ElemType)
    应当注意的是 逻辑位序 与 物理位序 之间相差 1：
        因为由数组实现，而数组下标(亦即物理位序)从 0 到 (MaxSize-1)
*/

#define MaxSize 30  // Just assume that it is 30

// typedef struct
// {
//     /* data */
// } ElemType;  // 定义一个抽象数据类型

// 然而课程中的ElemType 以char类型为例
// 因此有：
typedef char ElemType;

typedef struct 
{
    ElemType data[MaxSize];
    int length;
}SqList;  // 这里我们构造出一个顺序表数据类型

void CreateList(SqList *&L, ElemType a[], int n);
void InitList(SqList *&L);
void DestroyList(SqList *&L);
int ListEmpty(SqList *&L);
int ListLength(SqList *L);
int DispList(SqList *&L);
int GetElem(SqList *&L, int i,ElemType &e);
int LocateElem(SqList *&L, ElemType e);
int ListInsert(SqList *&L, int i, ElemType e);
int ListDelete(SqList *&L, int i, ElemType &e);
