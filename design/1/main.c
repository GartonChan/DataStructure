#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main()
{
    AdjMatrixGraph *g1;
    AdjListGraph *g2;
    g1 = CreateAdjMatrixGraph();
    DispAdjMatrixGraph(g1);
    g2 = CreateAdjListGraph();
    DispAdjListGraph(g2);
    return 0;
}
