#ifndef FIRSTGENERATOR_H
#define FIRSTGENERATOR_H

#include <unordered_map>
#include <vector>
#include <string>
#include "Symbol.h"

using namespace std;

class FirstGenerator
{
    public:
        FirstGenerator( unordered_map< string, vector< vector< Symbol > > > );
        unordered_map<string, vector< string >> get_first_set();
        virtual ~FirstGenerator();
    protected:
    private:
        unordered_map< string, vector< vector< Symbol > > > productions;
        unordered_map< string, vector< string > > first_set;
        vector< string > generate_firsts(string item);
};

#endif // FIRSTGENERATOR_H
