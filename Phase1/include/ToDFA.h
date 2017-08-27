#ifndef TODFA_H
#define TODFA_H
#include "Node.h"
#include "Edge.h"
#include <unordered_map>



class ToDFA
{
    public:
        ToDFA();
        virtual ~ToDFA();
        vector<Node*> get_epsilon_closure(vector<Node*> target_states);
        static vector<Node*> moveSym(vector<Node*> target_states,string symbol);
        vector<Node*> SubsetConstruction(vector<Node*> target_states,unordered_map<char,int> inputs);
        Node * getPhiState ();
    protected:
    private:
        Node * phi_state;
};

#endif // TODFA_H
