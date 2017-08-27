#include "FollowGenerator.h"
#include <algorithm>
#include <iostream>

FollowGenerator::FollowGenerator(unordered_map< string, vector< vector< Symbol* > > > _prod, unordered_map<string, vector< string > > _first)
{
    this->productions = _prod;
    this->first_set = _first;
}

unordered_map<string, vector< string > > FollowGenerator::get_follow_set()
{
    //initiailizing el follow_set
    for ( auto i = productions.begin(); i != productions.end(); ++i )
    {

        string item = i->first;
        vector< string > f;
        //el start symbol ba intialize el follow set bta3toh b '$'
        if(i == productions.begin())
        {
            f.push_back("$");
        }
        follow_set.insert({item, f});
    }

    //el flag da basta5demoh 3shan a3raf hafdl alef le had emta
    bool flag;
    do
    {
        flag = false;
        for ( auto p = productions.begin(); p != productions.end(); ++p )
        {
            string lhs = p->first;
            vector< vector< Symbol* > > rhs = p->second;

            //vector< vector< Symbol > >::iterator rhs_iter;
            //for(rhs_iter = rhs.begin(); rhs_iter != rhs.end(); rhs_iter++)
            for (vector<Symbol*> rhs_iter : rhs)
            {
                vector< Symbol* >::iterator symbol_iter;
                for(symbol_iter = rhs_iter.begin(); symbol_iter != rhs_iter.end(); symbol_iter++)
                {
                    Symbol &item = **symbol_iter;
                    unordered_map< string, vector< vector< Symbol* > > >::iterator prod_iter = productions.find(item.get_value());

                    //ha7ot el follow set bta3t el non terminal symbol hena
                    vector< string > follows;

                    // nonterminal followed by symbol
                    if(prod_iter != productions.end() && rhs_iter.end() != (symbol_iter + 1))
                    {
                        //bageeb el symbol elly ba3doh
                        Symbol &following_item = **(symbol_iter + 1);
                        unordered_map< string, vector< vector< Symbol* > > >::iterator prod_iter2 = productions.find(following_item.get_value());

                        // nonterminal followed by terminal
                        if(prod_iter2 == productions.end())
                        {
                            follows.push_back(following_item.get_value());
                        }
                        // nonterminal followed by nonterminal
                        else
                        {
                            unordered_map<string, vector< string > >::iterator first_iter = first_set.find(following_item.get_value());
                            vector< string > results = first_iter->second;
                            follows.insert(follows.end(), results.begin(), results.end());

                        //el first beta3 el symbol elly ba3doh feh epsilon
                            //vector< string >::iterator v_iter = results.find("");
                            //if(v_iter != results.end())
                            if ( std::find(results.begin(), results.end(), "\\L") != results.end() )
                            {
                                unordered_map<string, vector< string > >::iterator follow_iter = follow_set.find(lhs);
                                vector< string > v = follow_iter->second;
                                follows.insert(follows.end(), v.begin(), v.end());
                            }
                        }
                    }
                    // nonterminal not followed by anything
                    else if (prod_iter != productions.end())
                    {
                        unordered_map<string, vector< string > >::iterator follow_iter = follow_set.find(lhs);
                        vector< string > results = follow_iter->second;
                        follows.insert(follows.end(), results.begin(), results.end());
                    }
                    //el symbol hena terminal
                    else
                    {
                        continue;
                    }

                    if(follows.size() != 0)
                    {
                        flag = true;
                        //bazawed 3la el follow set el 2dema
                        unordered_map<string, vector< string > >::iterator follow_iterator = follow_set.find(item.get_value());
                        vector< string > res = follow_iterator->second;
                        follows.insert(follows.end(), res.begin(), res.end());
                        follow_iterator->second = follows;
                    }

                }
            }
        }
    }while(flag);


    return follow_set;
}


FollowGenerator::~FollowGenerator()
{
    //dtor
}
