#include "ToDFA.h"
#include "Edge.h"
#include "Node.h"
#include "stack"
#include "algorithm"

ToDFA::ToDFA()
{
    //ctor
}

vector<Node*> ToDFA::get_epsilon_closure(vector<Node*> target_states)
{
    stack <Node*> members;
    vector<Node*>::iterator it;
    vector<Node*> epsilon_closure;

    for(it=target_states.begin() ; it < target_states.end(); it++ ) {
        members.push(*it);
        epsilon_closure.push_back(*it);
    }
    while( !(members.empty()) )
    {
        vector<Edge>* children_edges = members.top()->get_children();
        int j= 0;
        members.pop();
        for (j=0 ; j<(*children_edges).size() ; j++) {
            if((*children_edges)[j].get_value()=="\\L")
            {
                members.push((*children_edges)[j].get_end_node());
                for (unsigned i=0; i<epsilon_closure.size(); i++)
                {
                    if(epsilon_closure.at(i)->get_node_name()==(*children_edges)[j].get_end_node()->get_node_name())
                       break;
                    if(i==epsilon_closure.size()-1)
                    {
                        epsilon_closure.push_back((*children_edges)[j].get_end_node());
                    }
                }
            }
        }

    }
    return epsilon_closure;
}

vector<Node*> ToDFA::moveSym(vector<Node*> target_states,string symbol)
{
    stack <Node*> members;
    vector<Node*>::iterator it;
    vector<Node*> in_closure;

    for(it=target_states.begin() ; it < target_states.end(); it++ ) {
        members.push(*it);
      //  in_closure.push_back(*it);
    }
    while( !(members.empty()) )
    {
        vector<Edge>* children_edges = members.top()->get_children();
        int j= 0;
        members.pop();
        for (j=0 ; j<(*children_edges).size() ; j++) {
            if((*children_edges)[j].get_value()== symbol)
            {
                if (in_closure.empty())
                    in_closure.push_back((*children_edges)[j].get_end_node());
                for (unsigned i=0; i<in_closure.size(); i++)
                {
                    if(in_closure.at(i)->get_node_name()==(*children_edges)[j].get_end_node()->get_node_name())
                       break;
                    if(i==in_closure.size()-1)
                    {
                        in_closure.push_back((*children_edges)[j].get_end_node());
                    }
                }
            }
        }
    }
    return in_closure;
}

vector<Node*> ToDFA::SubsetConstruction(vector<Node*> target_states,unordered_map<char,int> inputs)
{
    vector< pair<Node*, vector<Node*> > > D_states;
    vector<Node*> s0;   s0.push_back(*target_states.begin());
    vector<Node*> e_s0 = get_epsilon_closure(s0);
    sort (e_s0.begin(), e_s0.end());
    Node *node = new Node();
    node->set_node_name();
    D_states.push_back (make_pair(node, e_s0));

    int i=0;
    for (i=0 ; i < D_states.size() ; i++) {
        Node * dfaState = D_states[i].first;
        vector<Node*> e_move;
        for ( auto it = inputs.begin(); it != inputs.end(); ++it ) {
            string in_i(1,it->first);
            e_move = get_epsilon_closure(ToDFA::moveSym(D_states[i].second,in_i));
            sort (e_move.begin(), e_move.end());

            int k;
            for (k=0 ; k < D_states.size() ; k++) {
                vector<Node*>& nfaStates = D_states[k].second;
                if (nfaStates == e_move){
                    dfaState->add_child(D_states[k].first, in_i);
                    break;
                }
            }

            if(k == D_states.size()) {
                Node *n = new Node ();
                n->set_node_name();
                D_states.push_back (make_pair(n, e_move));
                dfaState->add_child(n, in_i);
            }
        }
    }
    for (int l=0 ; l<D_states.size() ; l++) {
        for (int ll=0 ; ll<D_states[l].second.size() ; ll++){
            if (D_states[l].second[ll]->is_acceptance_node())
            {
                D_states[l].first->set_acceptance_state(true);
                // token name //////////////////////////////
                string token_name = D_states[l].second[ll]->get_token();
                //cout << " token name : " <<D_states[l].second[ll]->get_token_type() << endl;
                if (token_name=="")
                    D_states[l].first->set_token(D_states[l].second[ll]->get_token_type());
                else
                    D_states[l].first->set_token(token_name);
                if (token_name == "int"||token_name == "boolean"||token_name == "float"||token_name == "if"||token_name == "else"||token_name == "while"){
                    break;
                }
                /////////////////////////////////

            }
        }
    }
    vector<Node*> MDFA;
    for (int i=0 ; i<D_states.size() ; i++)
    {
        MDFA.push_back(D_states[i].first);
        if (D_states[i].second.size() == 0)
            phi_state = D_states[i].first;
    }
    return MDFA;
}

Node * ToDFA::getPhiState()
{
    return phi_state;
}
ToDFA::~ToDFA()
{
    //ctor
}

