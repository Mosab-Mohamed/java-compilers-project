#include "Match.h"
#include "vector"
#include "Node.h"
#include "ToDFA.h"
#include "string"

Match::Match(Node * phi_state)
{
    this->phi_state = phi_state;
}


void Match::match_tokens(vector<Node*> MDFA , string input)
{
    int startPos = 0;
    while (startPos < (int)input.size())
    {
        int i, lastPos = -1;
        vector<Node*> Nodes;
        Nodes.clear();
        Nodes.push_back(MDFA[0]);
        Node * lastAccept = NULL;

        for (i = startPos; i < input.size(); i++)
        {
            string firstLetter(1,input[i]);
            Nodes = ToDFA::moveSym (Nodes, firstLetter);
            if (Nodes.size() == 0 || Nodes[0] == phi_state)
            {
                break;
            }
            if (Nodes[0]->is_acceptance_node())
            {
                lastAccept = Nodes[0];
                lastPos = i;
            }
        }
        if (lastAccept != NULL)
        {
            startPos = lastPos + 1;
            cout << lastAccept->get_token() << endl;
            tokens.push_back(lastAccept->get_token());
        }
        else
        {
            if (!isspace(input[startPos]))
                cout << "Error : " << input[startPos] << endl;

            ++startPos;
        }
    }
}

Match::~Match()
{
    //dtor
}
