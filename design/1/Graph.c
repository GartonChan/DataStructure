#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

AdjMatrixGraph *CreateAdjMatrixGraph()
{
    int n, e;
    AdjMatrixGraph *G;
    G = (AdjMatrixGraph *)malloc(sizeof(AdjMatrixGraph));
    int i, j, k;
    int weight;
    printf("请分别输入顶点数和边数：");
    scanf("%d%d", &n, &e);
    G->n = n;
    G->e = e;
    // 顶点信息输入
    for (i=0; i<n; i++)
    {
        printf("输入第%d个顶点的信息: ", i+1);
        scanf("%d", &(G->vertex[i].no));
    }
    // 边的信息输入
    for (k=0; k<e; k++)
    {
        printf("请输入边的两顶点序号: ");
        scanf("%d%d", &i, &j);
        i-=1;
        j-=1;  // 逻辑序号转换为物理序号
        printf("输入边的权重: ");
        scanf("%d", &weight);
        G->edges[i][j] = G->edges[j][i] = weight;
    }
    return G;
}

AdjListGraph *CreateAdjListGraph()
{
    int n, e;
    AdjListGraph *G;
    ArcType *pArc;
    int i, j, k;
    int weight;
    G = (AdjListGraph *)malloc(sizeof(AdjListGraph));
    printf("请分别输入顶点数和边数：");
    scanf("%d%d", &n, &e);
    G->n = n;
    G->e = e;
    // 顶点信息输入
    for(i=0; i<n; i++)
    {
        printf("输入第%d个顶点的信息: ", i+1);  // 录入顶点顺序表的信息
        scanf("%d", &(G->list[i].vertex.no)); 
        G->list[i].firstArc = NULL;  // 初始化边链表
    }
    // 边的信息输入
    for(k=0; k<e; k++)
    {
        printf("请输入边的两顶点的序号: ");
        scanf("%d%d", &i, &j);
        i-=1; j-=1;  // 逻辑序号转换为物理序号
        printf("请输入边的权重: ");
        scanf("%d", &weight);

        pArc = (ArcType *)malloc(sizeof(ArcType));
        pArc->next_vertex_no = j+1;  // 转换为逻辑序号，头插法建表
        pArc->weight = weight;
        pArc->nextArc = G->list[i].firstArc;
        G->list[i].firstArc = pArc;

        pArc = (ArcType *)malloc(sizeof(ArcType));
        pArc->next_vertex_no = i+1;  // 转换为逻辑序号，头插法建表
        pArc->weight = weight;
        pArc->nextArc = G->list[j].firstArc;
        G->list[j].firstArc = pArc;
    }
    return G;
}

void DispAdjMatrixGraph(AdjMatrixGraph *G)
{
    int i, j;
    printf("\t");
    for (i=0; i<G->n; i++)
    {
        printf("%3d\t", G->vertex[i].no);
    }
    printf("\n");
    for (i=0; i<G->n; i++)
    {
        printf("%3d\t", G->vertex[i].no);
        for(j=0; j<G->n; j++)
        {
            printf("%3d\t", G->edges[i][j]);
        }
        printf("\n");
    }

}

void DispAdjListGraph(AdjListGraph *G)
{
    int i;
    ArcType *pArc;
    for (i=0; i<G->n; i++)
    {
        pArc = G->list[i].firstArc;
        printf("%d->", i+1);
        while (1)
        {
            if (pArc == NULL)
            {
                printf("^");
                break;
            }
            printf("%d(%d)->", pArc->next_vertex_no, pArc->weight);
            pArc = pArc->nextArc;
        }
        printf("\n");
    }
}

AdjListGraph *MatToList(AdjMatrixGraph g)
{
    int i, j;
    int n = g.n;
    ArcType *pArc;
    AdjListGraph *G;
    G = (AdjListGraph *)malloc(sizeof(AdjListGraph));
    G->e = g.e;
    for (i=0; i<n; i++)  // initialize
    {
        G->list[i].firstArc = NULL;
    }   
    for (i=0; i<n; i++) 
    {
        for (j=n-1; j>=0; j--)
        {
            if(g.edges[i][j]!=0)
            {
                pArc = (ArcType *)malloc(sizeof(ArcType));
                pArc->nextArc = G->list[i].firstArc;  // 头插法建表
                G->list[i].firstArc = pArc;
                pArc->next_vertex_no = j;
            }
        }
    }
    return G;
}

AdjMatrixGraph *ListToMat(AdjListGraph g)
{
    int i, j;
    int n = g.n;
    ArcType *pArc;
    AdjMatrixGraph *G;
    G->n = g.n;
    G->e = g.e;
    for (i=0; i<n; i++)
    {
        pArc = g.list[i].firstArc;
        while (pArc != NULL)
        {
            j = pArc->next_vertex_no;
            G->edges[i][j] = 1;
            pArc = pArc->nextArc;
        }
    }
    return G;
}

int k = 0;  // using to record the num of visited vertex.
int VISITED[MAXNUM];  // flag array initialized as 0 means not be visited
/**
 * Depth-first Search 
 * g: Adjacency list Graph 
 * v: the beginning vertex 
 **/
void DFS(AdjListGraph *g, int v)
{
    ArcType *pArc;
    v -= 1;
    printf("%3d ", g->list[v].vertex.no);
    VISITED[v] = 1;
    k++;
    pArc = g->list[v].firstArc;
    while (pArc != NULL)
    {
        v = pArc->next_vertex_no;
        if (VISITED[v-1] == 0)
            DFS(g, v);
        if (k == g->n)
            return;
        pArc = pArc->nextArc;
    }
}

/** 
 * Breadth-first Search
 * g: Adjacency list Graph 
 * v: the beginning vertex
 **/
void BFS(AdjListGraph *g, int v)
{
    ArcType *pArc;
    int w, i;
    int k = 0;
    int queue[MAXNUM];
    int front = 0, rear = 0;
    int visited[MAXNUM];
    for (i=0; i<g->n; i++)  // initialize
        visited[i] = 0;
    printf("%3d ", v);
    v -= 1;
    visited[v] = 1;
    k++;
    rear = (rear + 1) % MAXNUM;
    queue[rear] = v;  // the beginning vertex enQueue
    while (front != rear)
    {
        if (k == g->n)
            break;
        front = (front + 1) % MAXNUM;
        w = queue[front];  // deQueue
        pArc = g->list[w].firstArc;
        while(pArc != NULL)
        {
            if (visited[pArc->next_vertex_no-1] == 0)
            {
                printf("%3d ", pArc->next_vertex_no);
                visited[pArc->next_vertex_no-1] = 1;
                rear = (rear + 1) % MAXNUM;  
                queue[rear] = pArc->next_vertex_no-1;  // enQueue
            }
            pArc = pArc->nextArc;
        }
    }
    printf("\n");
}
