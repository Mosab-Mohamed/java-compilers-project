#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H

#include "Graph.h"

#include <iostream>

using namespace std;
class GraphBuilder
{
    public:
        GraphBuilder();
        Graph* init_graph(string value);
        Graph* positive_clousure_operation(Graph* g1);
        Graph* clousure_operation(Graph* g1);
        Graph* or_operation(Graph* g1 , Graph* g2);
        Graph* and_operation(Graph* g1 , Graph* g2);
    private:
};

#endif // SIMPSONGRAPHBUILDER_H
