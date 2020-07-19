// Minimum spanning tree
#include "Graph.h"
#define MaxSize 20

typedef struct{
    int u;  // 起始顶点
    int v;  // 终止顶点
    int w;  // 边的权值
}Edge;   // 定义一个三元组类型存储边和两端顶点的信息

void Prim(MGraph g, int v);  // 构造性算法
void Kruskal(MGraph g);  

void InsertSort(Edge E[], int e);