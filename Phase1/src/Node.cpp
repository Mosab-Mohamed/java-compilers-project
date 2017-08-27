#include "Node.h"

int Node::node_count = 0;
Node::Node()
{
    //ctor
}

vector<Edge>* Node::get_children(){
    return &children;
}

void Node::add_child(Node* end_node, string value){
    Edge e(this,end_node , value);

    children.push_back(e);


}

void Node::set_acceptance_state(bool is_acceptance){
    this->is_acceptance = is_acceptance;
}

bool Node::is_acceptance_node(){
    return is_acceptance;
}

Node::~Node()
{
    //dtor
}
