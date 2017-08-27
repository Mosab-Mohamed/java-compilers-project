#ifndef PARSING_TABLE_H
#define PARSING_TABLE_H
#include<unordered_map>
#include<vector>
#include "Symbol.h"
#include<iostream>

using namespace std;

class Parsing_Table
{
    public:
        Parsing_Table(unordered_map<string , vector<string>>,
                              unordered_map<string , vector<string>>,
                              unordered_map< string,vector< vector<Symbol*> > >);

        vector<vector<vector<Symbol*>>> get_table();
        unordered_map<string , int> get_terminals_map();
        unordered_map<string , int> get_nonterminals_map();
        Symbol* get_starting_symbol();
    protected:
    private:
        unordered_map<string , vector<string>> first_set;
        unordered_map<string , vector<string>> follow_set;
        unordered_map< string,vector< vector<Symbol*> > > productions;
        unordered_map<string , int> terminals_map;
        unordered_map<string , int> nonterminals_map;
        void set_terminals();
        void set_nonterminals();
        int terminal_size = 0 ;
        int nonterminal_size = 0 ;
        Symbol* starting_symbol ;


};

#endif // PARSING_TABLE_H
