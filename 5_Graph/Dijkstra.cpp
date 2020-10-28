#include "Dijkstra.h"
#include <stdio.h>

void Dijkstra(MGraph g, int v){
    int dist[MAXV];  // dist即distance记录最短距离(每次添加顶点到集合S时后更新).
    int path[MAXV];  // 记录前驱的顶点,用于在后面输出路径.
    int s[MAXV];  // 集合S,标记各顶点是否在S集合内
    int mindis, i, j, k;
    for (i=0; i<g.n; i++){  // (1)初始化
        s[i] = 0;
        dist[i] = g.edges[v][i];  // 把边的信息赋给dist
        if (g.edges[v][i]<32767)  // 边不为无穷,就说明存在直连的顶点,令其前驱为顶点v
            path[i] = v;
        else path[i] = -1;  // -1表明未找到路径中的前驱顶点
    }
    for (i=1; i<g.n; i++){  // 循环n-1次, 记录S集合中的顶点个数, 为n时结束
        mindis = 32767; k =-1;  // k用于记录选中的顶点的编号
        for (j=0; j<g.n; j++){  // (2)选取不在S中且具有最小距离的顶点k加入S集合中
            if (s[j] == 0 && dist[j]<mindis){  
                k=j;
                mindis = dist[j];
            }  // 选取满足条件的顶点k
            if (k == -1)   
                break;  // 没有选出顶点k,说明是非连通图的情况,则跳出循环??? return??
            s[k]=1;
            for (j=0; j<g.n; j++)  // (3)需要修正U中各顶点的最小距离
                if (s[j]==0 && g.edges[k][j]<32767 && dist[k]+g.edges[k][j]<dist[j]){  // g.edges[k][j]<32767不会影响条件的判断结果, 此处表明小于无穷是指的k-j之间存在边
                    dist[j] = dist[k] + g.edges[k][j];
                    path[j] = k;
                }
        }
    }
    DispPath(dist, path, s, g.n, v);  // 输出最短路径
}

void Ppath(int path[], int i, int v){  // 从后往前查找路径上的顶点,实现从后往前倒
    int k;
    k = path[i];
    if(k == v)
        return ;  // 找到了源点v后就返回(递归的临界条件)
    Ppath(path, k, v);
    printf("%d,",k);  // 通过递归实现,倒着将路径的各顶点(除去源点和终点)正向(源点->终点)输出
}

void DispPath(int dist[], int path[], int s[], int n, int v){  // 输出从源点v到其他顶点的最短路径
    int i;
    for (i=0; i<n; i++){
        if(s[i] == 1){
            printf("%d到%d的最短路径长度为:%d\t路径为:", v, i, dist[i]);
            printf("(%d", v);  // 输出路径的源点
            Ppath(path, i, v);  // 输出路径的中间点
            printf("%d\n", i);  // 输出路径的终点
        }
        else
            printf("%d到%d不存在路径\n", v, i);
    }
}