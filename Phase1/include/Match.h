#ifndef MATCH_H
#define MATCH_H
#include "vector"
#include "string"
#include "Node.h"



class Match
{
    public:
        Match(Node *);
        virtual ~Match();
        void match_tokens(std::vector<Node*> MDFA, std::string input);
        std::vector<string> Return_Tokens(){
            return tokens;
        }
    protected:
    private:
        Node * phi_state;
        std::vector<string> tokens;
};

#endif // MATCH_H
