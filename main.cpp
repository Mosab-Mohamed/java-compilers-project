#include <iostream>
#include"Symbol.h"
#include<vector>
#include<string>
#include<stack>
#include "Parsing_Table.h"


using namespace std;

vector<string> get_tokens();

int main()
{
    /*
    vector< vector<Symbol*> > v1 ;

    vector<Symbol*> v2 ;
    Symbol* s1 = new Symbol("mosap");
    Symbol* s2 = new Symbol("mohamed");
    Symbol* s3 = new Symbol("khames");
    Symbol* s4 = new Symbol("mohamed");
    Symbol* s5 = new Symbol("mohamed");
    Symbol* s6 = new Symbol("hemeda");
    v2.push_back(s1);
    v2.push_back(s2);
    v2.push_back(s3);
    v2.push_back(s4);

    vector<Symbol*> v17 ;
    v17.push_back(new Symbol("ddddddd"));
    v17.push_back(new Symbol("rrrrrrr"));
    v17.push_back(new Symbol("eeeeee"));
    v17.push_back(new Symbol("deeqqqqqqqq"));
    v1.push_back(v2);
    v1.push_back(v17);


    for( vector<Symbol*> v : v1 )
    {
        for( Symbol* ss : v )
        {
            cout<< ss->get_value()<<"\n";
        }
    }
    */

    /********************************************************************/

    /** test table **/


    unordered_map< string,vector< vector<Symbol*> > > productions_set ;
    unordered_map<string , vector<string>> follow ;
    unordered_map<string , vector<string>> first ;

    vector<Symbol*> v3 ;
    v3.push_back(new Symbol("T"));
    v3.push_back(new Symbol("E'"));
    vector< vector<Symbol*> > vv1 ;
    vv1.push_back(v3);

    productions_set.insert(pair< string,vector<vector<Symbol*>>>("E",vv1));


    vector<Symbol*> v4 ;
    v4.push_back(new Symbol("+"));
    v4.push_back(new Symbol("T"));
    v4.push_back(new Symbol("E'"));

    vector<Symbol*> v8 ;
    v8.push_back(new Symbol("\\L"));

    vector< vector<Symbol*> > vv2 ;
    vv2.push_back(v4);
    vv2.push_back(v8);

    productions_set.insert(pair< string,vector<vector<Symbol*>>>("E'",vv2));


    vector<Symbol*> v5 ;
    v5.push_back(new Symbol("F"));
    v5.push_back(new Symbol("T'"));
    vector< vector<Symbol*> > vv3 ;
    vv3.push_back(v5);

    productions_set.insert(pair< string,vector<vector<Symbol*>>>("T",vv3));


    vector<Symbol*> v6 ;
    v6.push_back(new Symbol("*"));
    v6.push_back(new Symbol("F"));
    v6.push_back(new Symbol("T'"));

    vector<Symbol*> v9 ;
    v9.push_back(new Symbol("\\L"));

    vector< vector<Symbol*> > vv4 ;
    vv4.push_back(v6);
    vv4.push_back(v9);

    productions_set.insert(pair< string,vector<vector<Symbol*>>>("T'",vv4));


    vector<Symbol*> v7 ;
    v7.push_back(new Symbol("("));
    v7.push_back(new Symbol("E"));
    v7.push_back(new Symbol(")"));

    vector<Symbol*> v10 ;
    v10.push_back(new Symbol("id"));

    vector< vector<Symbol*> > vv5 ;
    vv5.push_back(v7);
    vv5.push_back(v10);

    productions_set.insert(pair< string,vector<vector<Symbol*>>>("F",vv5));

    ///////////////////////////

    first.insert(pair< string,vector<string> >("F",{"(","id"}));
    first.insert(pair< string,vector<string> >("T'",{"*","\\L"}));
    first.insert(pair< string,vector<string> >("T",{"(","id"}));
    first.insert(pair< string,vector<string> >("E'",{"+","\\L"}));
    first.insert(pair< string,vector<string> >("E",{"(","id"}));
    first.insert(pair< string,vector<string> >("+",{"+"}));
    first.insert(pair< string,vector<string> >("\\L",{"\\L"}));
     first.insert(pair< string,vector<string> >("*",{"*"}));
     first.insert(pair< string,vector<string> >("(",{"("}));
     first.insert(pair< string,vector<string> >("id",{"id"}));

    follow.insert(pair< string,vector<string> >("E",{"$",")"}));
    follow.insert(pair< string,vector<string> >("E'",{"$",")"}));
    follow.insert(pair< string,vector<string> >("T",{"+",")","$"}));
    follow.insert(pair< string,vector<string> >("T'",{"+",")","$"}));
    follow.insert(pair< string,vector<string> >("F",{"+","*",")","$"}));


    Parsing_Table* pt = new Parsing_Table(first,follow,productions_set);

    vector<vector<vector<Symbol*>>> tab2 = pt->get_table();

    unordered_map<string , int> terminals = pt->get_terminals_map();
    unordered_map<string , int> nonterminals = pt->get_nonterminals_map();


    for( auto it1 = nonterminals.begin(); it1 != nonterminals.end(); ++it1 )
    {
        for( auto it2 = terminals.begin(); it2 != terminals.end(); ++it2 )
        {
            if(tab2[it1->second][it2->second].size()>0)
            {
                cout<<"[ "<<it1->first<<" , "<<it2->first<<" ]"<<" = { ";
                for(int k=0 ; k<tab2[it1->second][it2->second].size() ; k++)
                {
                    cout<<tab2[it1->second][it2->second][k]->get_value()<<" , ";
                }
                cout<< "}\n";
            }
            else
            {
                cout<<"[ "<<it1->first<<" , "<<it2->first<<" ]"<<" ==> error\n";
            }

        }


    }

    cout<<"\n\nstarting symbol --> "<<pt->get_starting_symbol()<<"\n";



    /********************************************************************/

    /** stack test **/

    /*
    stack<Symbol*> parser;

    parser.push(new Symbol("$"));
    parser.push(new Symbol("S"));

    unordered_map<string , int> terminals ;
    terminals.insert(pair<string,int>("a",0));
    terminals.insert(pair<string,int>("b",1));
    terminals.insert(pair<string,int>("$",2));

    unordered_map<string , int> nonterminals ;
    nonterminals.insert(pair<string,int>("S",0));
    nonterminals.insert(pair<string,int>("B",1));

    vector<vector<vector<Symbol*>>> table( nonterminals.size(),vector<vector<Symbol*>>( terminals.size(),vector<Symbol*>() ) );

    Symbol* a = new Symbol("a");
    a->set_terminal(true);
    Symbol* b = new Symbol("b");
    b->set_terminal(true);

    vector<Symbol*> v1;
    v1.push_back(a);
    v1.push_back(new Symbol("B"));
    v1.push_back(a);
    table[ nonterminals.find( "S" )->second ][ terminals.find( "a" )->second ] = v1 ;

    vector<Symbol*> v2;
    v2.push_back(new Symbol("\\L"));
    table[ nonterminals.find( "B" )->second ][ terminals.find( "a" )->second ] = v2 ;

    vector<Symbol*> v3;
    v3.push_back(b);
    v3.push_back(new Symbol("B"));
    table[ nonterminals.find( "B" )->second ][ terminals.find( "b" )->second ] = v3 ;

    //input should be get from phase1 of the project and it is get token by token
    string input = "abba$";
    int index = 0;

    while(! (parser.empty()) )
    {
        Symbol* top = parser.top();
        //cout<<"stack:: "<<top->get_value()<<"("<<top->is_terminal()<<")"<<"   input:: "<<input[index]<<"\n";

        if(top->get_value()=="\\L")
        {
            parser.pop();
            continue;
        }

        if(top->get_value()=="$" && string(1,input[index])=="$")
        {
            cout<<"finished parsing successfully :D\n";
            parser.pop();
            index++;
            break;
        }

        else if(top->get_value()==string(1,input[index]) && top->is_terminal())
        {
            //cout<<"enter here \n";
            parser.pop();
            index++;
            continue;
        }

        else if(! (top->is_terminal()) )
        {
            if(table[ nonterminals.find( top->get_value() )->second ][ terminals.find( string(1,input[index]) )->second ].size() > 0)
            {
                vector<Symbol*> table_entry = table[ nonterminals.find( top->get_value() )->second ][ terminals.find( string(1,input[index]) )->second ];
                parser.pop();
                cout<<top->get_value()<<" --> ";
                for(int i=table_entry.size()-1 ; i>=0 ; i--)
                {
                    cout<<table_entry[i]->get_value();
                    parser.push(table_entry[i]);
                }
                cout<<"\n";

            }
            else
            {

                //error
            }
        }

        else
        {

            //error
        }


    }

    */


    /****************************************************************/

/*
    stack<Symbol*> parser;

    vector<string> tokens = get_tokens();

    Parsing_Table* pt ;//= new Parsing_Table(first,follow,productions_set);

    vector<vector<vector<Symbol*>>> table = pt->get_table();

    unordered_map<string , int> terminals = pt->get_terminals_map();
    unordered_map<string , int> nonterminals = pt->get_nonterminals_map();

    Symbol* starting_symbol = pt->get_starting_symbol();


    parser.push(new Symbol("$"));
    parser.push(starting_symbol);

    int index = 0;

    while(! (parser.empty()) )
    {
        Symbol* top = parser.top();
        //cout<<"stack:: "<<top->get_value()<<"("<<top->is_terminal()<<")"<<"   input:: "<<input[index]<<"\n";

        if(top->get_value()=="\\L")
        {
            parser.pop();
            continue;
        }

        if(top->get_value()=="$" && tokens[index]=="$")
        {
            cout<<"finished parsing successfully :D\n";
            parser.pop();
            index++;
            break;
        }

        else if(top->get_value()==tokens[index] && top->is_terminal())
        {
            //cout<<"enter here \n";
            parser.pop();
            index++;
            continue;
        }

        else if(! (top->is_terminal()) )
        {
            if(table[ nonterminals.find( top->get_value() )->second ][ terminals.find( tokens[index] )->second ].size() > 0)
            {
                vector<Symbol*> table_entry = table[ nonterminals.find( top->get_value() )->second ][ terminals.find( tokens[index] )->second ];
                parser.pop();
                cout<<top->get_value()<<" --> ";
                for(int i=table_entry.size()-1 ; i>=0 ; i--)
                {
                    cout<<table_entry[i]->get_value();
                    parser.push(table_entry[i]);
                }
                cout<<"\n";

            }
            else
            {

                //error
            }
        }

        else
        {

            //error
        }


    }
*/
}

vector<string> get_tokens()
{
    vector<string> v;
    return v;
}
