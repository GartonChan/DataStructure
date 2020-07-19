// Minimum spanning tree
#include <stdio.h>
#include <stdlib.h>
#include "MST.h"


void Prim(MGraph g, int v){  // v是任一顶点(初始点), 邻接矩阵存放
    int lowcost[MAXV];  // 用于记录U到V-U的边的最小权值
    int min;  // 选出最小权值
    int closest[MAXV];  // 存储该边依附的在U中的顶点
    int i, j, k;
    for (i=0; i<g.n; i++){
        lowcost[i] = g.edges[v][i];  // 给lowcost和closest置初值
        closest[i] = v;
    }
   
    for (i=1; i<g.n; i++){  // 找出n-1个顶点
        min = 32767;  // 用32767表示无穷大
        k = -1;  // k记录选中的顶点,此处-1表示未选中
        for (j=0; j<g.n; j++)  // 从V-U找出离U最近的顶点k
            if (lowcost[j] != 0 && lowcost[j] < min){
                k = j;
                min = lowcost[j];
            }
        if (k == -1)  // 如果是非连通图,全是无穷的话无法选出vk.考虑这种情况跳出循环结束
            break;
        printf("边(%d, %d)权为:%d\n", closest[k], k, min);
        lowcost[k] = 0;  // 让其在lowcost值为0表明已加入到生成树中(vk已并入U)
        for (j=0; j<g.n; j++){
            if (g.edges[k][j] < lowcost[j])  // 更新侯选边信息,以便下次循环挑选最小权值的边和结点
            {
                lowcost[j] = g.edges[k][j];
                closest[j] = k;
            }
        }
    }
}

void Kruskal(MGraph g){
    int i, j, u1, v1, sn1, sn2, k;
    int vset[MAXV];
    Edge E[MaxSize];  // 存放图G中的所有边
    k = 0;  // E数组下标从0开始
    for (i=0; i<g.n; i++){  // 给E数组赋予各条边的信息
        for (j=i+1; j<g.n; j++)  // 无向图的邻接矩阵按主对角线对称,扫描上三角或下三角即可
            if (g.edges[i][j]!=0 && g.edges[i][j]!=32767){
                E[k].u = i;
                E[k].v = j;
                E[k].w = g.edges[i][j];
                k++;
            }
    }  // 完成提取所有边的信息
    InsertSort(E, g.e);  // 对E数组按权值递增排序
    for (i=0; i<g.n; i++)  // 初始化辅助数组
        vset[i] = i; 
    k = 1;  // 表明当前构造最小生成树的第k条边,初值为1
    j = 0;  // E数组中 边的下标,初值为0
    while (k<g.n && j<g.e){  // 生成边数小于n 并且 所有边未被处理完
        u1 = E[j].u;  // 取一条边的两顶点.
        v1 = E[j].v;
        sn1 = vset[u1];  // 分别得到两个顶点所属的集合编号,以判断是否会构成回路(相等就会构成)
        sn2 = vset[v1];
        if (sn1 != sn2){  // 这两顶点属于不同的集合->可以成为MST的一条边
            printf("(%d, %d):%d\n", u1, v1, E[j].w);
            k++;  // k自增,表明边数加1
        }
        for (i=0; i<g.n; i++){  // 两个集合统一编号, (这里只让它变成相同的即可)
            if(vset[i] == sn2)
                vset[i] = sn1;  // 编号为sn2的改为sn1
        }
        j++;  // j自增,让下次循环处理下一条边
    }
}