#include <stdio.h>
#include <stdlib.h>
// #include "Graph.h"
#include "MST.h"

int main()
{
    AdjMatrixGraph *g;
    g = CreateAdjMatrixGraph();
    Prim(*g, 1);
    KrusKal(*g);
    return 0;
}