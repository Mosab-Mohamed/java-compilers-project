#ifndef PARSER_H
#define PARSER_H
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;


class Parser
{
    public:
        Parser();
        void GetNonTerminals();
        unordered_map<string,vector<vector<Symbol*> > > Parse();
        void Print();
        unordered_map<string,vector<vector<Symbol*> > > Convert(unordered_map<string,vector<vector<Symbol*>* >* > );
        virtual ~Parser();
    protected:
    private:
        unordered_map<string,vector<vector<Symbol*>* >* > map_out;
};

#endif // PARSER_H
