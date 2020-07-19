#include <stdio.h>
#include <stdlib.h>
#define MaxSize 30

typedef char ElemType;

typedef ElemType SqBTree[MaxSize];  
// 使用typedef定义SqBTree为类型为ElemType的数组类型

int main(int argc, char const *argv[])
{
    SqBTree a;
    ElemType b[MaxSize];
    printf("sizeof(SqBTree a) = %d\n\
sizeof(ElemType b[MaxSize]) = %d\n", \
            sizeof(a), sizeof(b));
    return 0;
}