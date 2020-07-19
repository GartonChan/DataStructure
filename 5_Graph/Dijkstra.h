#include "Graph.h"

void Dijkstra(MGraph g, int v);  // 迪克斯特拉算法
void Ppath(int path[], int i, int v);  // 从后往前查找路径上的顶点,实现从后往前倒
void DispPath(int dist[], int path[], int s[], int n, int v);  // 输出从源点v到其他顶点的最短路径
