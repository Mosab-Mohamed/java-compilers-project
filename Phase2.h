#ifndef PHASE2_H
#define PHASE2_H
#include <Symbol.h>
#include <unordered_map>
#include <vector>
using namespace std;

class Phase2
{
    public:
        Phase2();
        void GetNonTerminals();
        unordered_map<string,vector<vector<Symbol*>* >* > Parse();
        void Print();
        virtual ~Phase2();
    protected:
    private:
        unordered_map<string,vector<vector<Symbol*>* >* > map_out;
};

#endif // PHASE2_H
