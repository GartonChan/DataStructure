#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"

// 对于同一个图而言,两种存储方式之间可以相互转换.
// 以下实现对无向表和有向表均有效.

/* 邻接矩阵 -> 邻接表
    按行或是按列扫描 找到非零元素,说明有边,则在链表中插入一条边
    扫完一行或是一列就能有一条单链表建立完成,扫完n行就能建立n条,建立起邻接表
*/
void MatToList(MGraph g, ALGraph *&G){
    int i, j, n = g.n;  // n是顶点数, 避免下面一直写g.n
    ArcNode *p;
    G = (ALGraph *)malloc(sizeof(ALGraph));
    G->n = n;  // 现将矩阵的基本信息交给邻接表
    G->e = g.e;
    for(i=0; i<n; i++)  // 邻接表的所有表头结点的指针域初始化为空
        G->adjlist[i].firstarc = NULL;
    for(i=0; i<n; i++)  // 双循环扫描
        for(j=n-1; j>=0; j--){  // 这里使用头插法建表,所以我们倒着从n-1 -> 0
            if(g.edges[i][j] != 0){  // 邻接矩阵 (i,j)处的元素不为零时,即存在边需要转换到邻接表
                p = (ArcNode *)malloc(sizeof(ArcNode));  // 开辟新的边结点
                p->nextarc = G->adjlist[i].firstarc;  // 头插法建表
                G->adjlist[i].firstarc = p;  // 头插法建表   ->  理解此处指针变化的含义
                p->adjvex = j;  // j即为vi的邻接点的编号,赋给新建的边结点记录这条边的终点位置
            }
        }
}  // O(n*n)


void ListToMat(ALGraph *G, MGraph &g){
// 逐条链表扫描,一个顶点到另一个顶点,每扫描一个顶点就会在邻接表产生一个1的元素
    int i, n = G->n;
    ArcNode *p;
    g.n = n;
    g.e = G->e;  // 复制基本信息
    // 由邻接表建立邻接矩阵
    for(i=0; i<n; i++){  // 逐个表头结点(的单链表)进行扫描
        p = G->adjlist[i].firstarc;  // p直接指向数组第i个元素的第一个边结点
        while(p){  // p指向非空时
            g.edges[i][p->adjvex] = 1;  // 矩阵的(vi,p->adjvex)的元素为1, p->adjvex即vj
            p = p->nextarc;  // 让p指向下一个边结点直至扫描完这条单链表(即p==NULL).
        }  // 继续for循环扫描下一条链表直至扫描完全部链表.
    }
}  // 外循环n次, 内循环不是n次,对于无向图一条边会被扫描两次,while扫描一共是2e次,p被赋为表头结点n次
// O(n+2e)  2e是对于无向图中边的扫描次数而言


int k=0;
int VISITED[MAXV];  // 标志数组,全局数组,并且初始时所有元素均为0表示所有结点未被访问
void DFS(ALGraph *G, int v){  // v表示初始点编号
    ArcNode *p;
    printf("%3d ", v);  // 输出被访问顶点的编号
    VISITED[v] = 1;  // 在标志数组中给这个顶点的位置放1
    k++;  // 访问顶点个数+1
    p = G->adjlist[v].firstarc;  // p指向顶点v的第一条边.
    while(p != NULL){  // p指向非空时)完成对相邻结点的遍历(避免还有相邻结点visited[..]=0而未被访问的)
        if(VISITED[p->adjvex] == 0)
            DFS(G, p->adjvex);  // 若有相邻顶点未访问,递归访问它
        if(k == G->n) return ;  // 已访问完毕就直接回退,减少对后续边结点的扫描. 用return(函数出口)来结束当前的递归函数
        p = p->nextarc;  // p指向该顶点的下一条边
    }
}  // 递归代码简单,但反复调用其实效率不高,并且不易于理解.
// 用全局变量k进行优化(减少无用的回退(由递归导致)),记录已访问过的顶点数
// 一条一条路径地走,走到底(无路可走)


void BFS(ALGraph *G, int v){
    ArcNode *p;
    int w, i;
    int k = 0;  // 跟DFS类似地进行优化
    // 定义一个循环队列, 迷宫问题用的是非循环队列,因为迷宫问题需要输出完整的路径,出队元素不能被真正删除,因而不能使用循环队列
    int queue[MAXV], front = 0, rear = 0;  
    int visited[MAXV];  // 定义存放顶点访问信息的标志数组
    for(i=0; i<G->n; i++)  // 标志数组初始化
        visited[i] = 0;
    printf("%3d ", v);  // 输出访问的顶点
    visited[v] = 1;
    k++;
    rear = (rear + 1) % MAXV;  // v进队
    queue[rear] = v;
    while(front != rear){  // 只要队列非空就循环执行
        if(k == G->n)  // 加入优化,避免访问完成后仍进行扫描
            break;
        front = (front + 1) % MAXV;  // 队头元素出队并赋给w
        w = queue[front];
        p = G->adjlist[w].firstarc;  // 沿着w的单链表找它的邻接点,全部入队列
        while(p != NULL){
            if(visited[p->adjvex] == 0){  // p->adjvex 为w的邻接点的顶点编号
                printf("%3d ", p->adjvex);  // 先对其访问
                visited[p->adjvex] = 1;  // 修改访问信息(表明已访问)
                rear = (rear + 1) % MAXV;  // 该顶点(w的邻接点)入队.
                queue[rear] = p->adjvex;
            }
            p = p->nextarc;  // p指向w的下一个邻接点
        }
    }  // 队列为空,说明已经遍历完成
    printf("\n");
}// 一圈一圈地往外扩


// 非连通图的遍历
void GS(ALGraph *G){
    int i;
    for(i=0; i<G->n; i++)  // 每个顶点都作为初始点进行考虑以遍历所有顶点(只要该结点未被访问过就执行遍历算法)
        if(VISITED[i] == 0)  // 循环次数看有多少个连通分量
            DFS(G, i);  // 按照要求使用的算法进行递归遍历
}