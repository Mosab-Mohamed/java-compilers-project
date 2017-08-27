#include "FirstGenerator.h"

FirstGenerator::FirstGenerator(unordered_map< string, vector< vector< Symbol >>> _productions)
{
    this->productions = _productions;
}

unordered_map<string, vector< string >> FirstGenerator::get_first_set()
{
    for ( auto p = productions.begin(); p != productions.end(); ++p )
    {
        string lhs = p->first;
        vector< vector< Symbol >> rhs = p->second;

        vector< string > firsts;

        vector< vector< Symbol >>::iterator it;
        for(it = rhs.begin(); it != rhs.end(); it++)
        {
            vector< Symbol > expr = *it;

            Symbol s = expr.front();
            string symbol_value = s.get_value();
            vector< string > results = generate_firsts(symbol_value);
            firsts.insert(firsts.end(), results.begin(), results.end());
        }

        first_set.insert({lhs, firsts});
    }
    return first_set;
}

vector< string > FirstGenerator::generate_firsts(string item)
{
    vector< string > firsts;
    unordered_map<string, vector< vector< Symbol > > >::iterator iter;
    iter = productions.find(item);

    if(iter == productions.end())
    {
        firsts.push_back(item);
    }
    else
    {
        vector< vector< Symbol > >::iterator it;
        for(it = iter->second.begin(); it != iter->second.end(); it++)
        {
            vector< Symbol > expr = *it;

            Symbol s = *expr.front();
            string symbol_value = s.get_value();
            vector< string > results = generate_firsts(symbol_value);
            firsts.insert(firsts.end(), results.begin(), results.end());
        }
    }
    return firsts;
}

FirstGenerator::~FirstGenerator()
{
    //dtor
}
