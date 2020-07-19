#define MAXV 10

// 邻接矩阵 (顺序存储
typedef struct 
{
    int no;  // 顶点编号, 标识顶点
    // VexInfoType vexinfo;  // 顶点其他信息, 通用类型标识符. 此处用不到
}VertexType;  // 定义顶点类型

typedef struct{  // 邻接矩阵存储的图的结构类型
    int edges[MAXV][MAXV];  // 邻接矩阵,能表征结点之间边的关系
    int n, e;  // 顶点数, 边数, 为了避免每次都计算边和顶点的数量
    VertexType vexs[MAXV];  // 存放顶点信息,由上个定义可知,此处就只是顶点编号
}MGraph;  // matrixGraph,定义邻接矩阵存储的图类型


// 邻接表 (顺序和链式结合
/*
    表结点(边结点)
        adjvex: 指示与顶点vi邻接的点在图中的位置,一般为顶点编号
        nextarc: 指针,指向下一条边或弧对应的结点
        info: 存储与边或弧相关的信息,如权值等.

    表头结点
        data: 存储顶点的vi的名称/编号或其他信息
        firstarc: 指针,指向链表中第一个表接点

*/
typedef struct Anode{  // 定义边结点的结构类型
    int adjvex;  // 该边的终点位置(即下一个边结点)
    struct Anode *nextarc;  // 指向下一条边(下一个边结点)的指针
    // ArcInfoType arcinfo;  // 该边的相关信息(无其他信息就可以不要)
}ArcNode;  // 定义边结点类型

typedef struct Vnode{  // 定义邻接表头结点的结构类型
    VertexType data;  // 顶点信息
    ArcNode *firstarc;  // 指向第一条边(第一个边结点)
}VNode;  // 定义表头结点类型

typedef VNode AdjList[MAXV];  // AdjList邻接表类型(用于存放表头结点的顺序表)

typedef struct{
    AdjList adjlist;  // 邻接表
    int n,e;  // 顶点数n和边数e
}ALGraph;  // 定义邻接表存储的图类型


void MatToList(MGraph g, ALGraph *&G);
void ListToMat(ALGraph *G, MGraph &g);

void DFS(ALGraph *G, int v);
void BFS(ALGraph *G, int v);

//非连通图的遍历
void GS(ALGraph *G);
