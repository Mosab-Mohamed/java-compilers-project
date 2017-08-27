#include "GraphBuilder.h"

GraphBuilder::GraphBuilder()
{
    //ctor
}


/** initiate graph with two nodes **/
Graph* GraphBuilder::init_graph(string value){
    Graph* graph = new Graph();
    Node * start_node = new Node();
    Node * end_node = new Node();

    start_node->set_node_name();
    end_node->set_node_name();

    start_node->add_child(end_node, value);

    graph->set_start_node(start_node);
    graph->set_end_node(end_node);

    graph->set_graph_size(2);

    return graph;
}

/** AB **/
Graph* GraphBuilder::and_operation(Graph* g1 , Graph* g2){
        Graph *graph = new Graph();

        //Connect the two graphs
        g1->get_end_node()->add_child(g2->get_start_node() , "\\L");

        graph->set_start_node(g1->get_start_node());
        graph->set_end_node(g2->get_end_node());

        int graph_size = g1->get_graph_size() + g2->get_graph_size();
        graph->set_graph_size(graph_size);

        return graph;
}

/** A|B **/
Graph* GraphBuilder::or_operation(Graph* g1 , Graph* g2){
    Graph* graph = new Graph();
    Node * start_node = new Node();
    Node * end_node = new Node();

    start_node->set_node_name();
    end_node->set_node_name();

    // Connect the new End node to the two graphs
    g1->get_end_node()->add_child(end_node,"\\L");
    g2->get_end_node()->add_child(end_node,"\\L");

    //Connect the new Start node to the two graphs
    start_node->add_child(g1->get_start_node(),"\\L");
    start_node->add_child(g2->get_start_node(),"\\L");

    // Add the start and end nodes to the graph
    graph->set_start_node(start_node);
    graph->set_end_node(end_node);

    //Graph size
    int graph_size = g1->get_graph_size() + g2->get_graph_size() + 2;
    graph->set_graph_size(graph_size);

    return graph;
}

/** A* **/
Graph* GraphBuilder::clousure_operation(Graph* g1){
    Graph* graph = new Graph();
    Node* start_node = new Node();

    start_node->set_node_name();

    // 1..*
    start_node->add_child(g1->get_start_node() , "\\L");
    g1->get_end_node()->add_child(g1->get_start_node(),"\\L");

    //0..*
    start_node->add_child(g1->get_end_node() , "\\L");

    // Add the start and end nodes to the graph
    graph->set_start_node(start_node);
    graph->set_end_node(g1->get_end_node());

    //Graph Size
    int graph_size = g1->get_graph_size() + 1;
    graph->set_graph_size(graph_size);

    return graph;
}

/** A+ **/
Graph* GraphBuilder::positive_clousure_operation(Graph* g1){
    Graph * graph = new Graph();
    Node * end_node = new Node();

    end_node->set_node_name();

    // 1..+
    g1->get_end_node()->add_child(g1->get_start_node(),"\\L");

    // finish
    g1->get_end_node()->add_child(end_node,"\\L");

    // Add the start and end nodes to the graph
    graph->set_start_node(g1->get_start_node());
    graph->set_end_node(end_node);

    //GRaph Size
    int graph_size = g1->get_graph_size() + 1;
    graph->set_graph_size(graph_size);

    return graph;
}
