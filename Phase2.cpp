#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <Symbol.h>
#include "Phase2.h"
using namespace std;

Phase2::Phase2()
{

}

void Phase2::GetNonTerminals()
{

    ifstream myfile ("CFG.txt");
    string line;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            stringstream ss;
            int i=0;
            while ((line[i]>=65 && line[i]<=90) || line[i]==95){
                ss << line[i];
                i++;
            }
            if (i!=0)
            {
                string name = ss.str();
                //vector<Symbol*> s;
                vector<vector<Symbol*> *>* prod = new vector<vector<Symbol*>*>();
                //prod.push_back(s) ;
                map_out.insert(pair<string,vector<vector<Symbol*> *>* >(name,prod));
            }
        }
        myfile.close();
    }
    else
        cout << "Unable to open file in GetNonTerminals";
}

unordered_map<string,vector<vector<Symbol*>* >* > Phase2:: Parse()
{
    GetNonTerminals();
    ifstream myfile ("CFG.txt");
    string line;
    if (myfile.is_open())
    {
        string LFS;
        while ( getline (myfile,line) )
        {
            stringstream  stream(line);
            string  word,firstword;
            bool b_or=false,b_and=false;
            int or_count=0;
            stream >> firstword;
            if (firstword!="|")
                LFS = firstword;
            while (stream >> word)
            {
                if (word=="::=")
                    continue;
                if (word=="|")
                {
                    if (or_count==0){
                        if (map_out.find(LFS)->first == "INFIX_OPERATOR")
                            or_count++;
                        b_and=false;
                        continue;
                    }
                }
                or_count=0;
                if (firstword=="|") b_and=false;
                bool isTerminal = false;
                vector<vector<Symbol*>*>* v = map_out.find(LFS)->second;
                vector<Symbol*>* symbols = new vector<Symbol*>() ;
                if (map_out.find(word)!=map_out.end())
                {
                    //cout << "NonTerminal" << " " <<  word << endl;
                    isTerminal=false;

                } else {
                    //cout << "Terminal" << " " <<  word << endl;
                    isTerminal=true;

                }
                if (b_and)
                {
                    symbols = v->back();
                    symbols->push_back(new Symbol(word,isTerminal));
                }
                else
                {
                    symbols->push_back(new Symbol(word,isTerminal));
                    v->push_back(symbols);
                }
                b_and=true;
                //cout << map_out.find(LFS)->first << " size : " << v->size() << endl;
            }
        }
    }
    else
        cout << "Unable to open file in Parse";

    return map_out;
}

void Phase2::Print()
{
    for ( auto it = map_out.begin(); it != map_out.end(); ++it )
    {
        cout << it->first << " ::= " ;
        vector<vector<Symbol*>*>* vv = it->second ;
        for (int i=0 ; i<vv->size() ; i++)
        {
            vector<Symbol*>* vvv = vv->at(i);
            for (int j=0 ; j<vvv->size() ; j++)
            {
                    cout << vvv->at(j)->getValue() << " " ;
            }
            cout << "| "  ;
        }
        cout << endl ;

    }
}



Phase2::~Phase2()
{
    //dtor
}
