#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main()
{
    AdjListGraph *g;
    g = CreateAdjListGraph();
    DFS(g, 1);
    printf("\n");
    BFS(g, 1);
    return 0;
}
