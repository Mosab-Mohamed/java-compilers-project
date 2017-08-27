#include <iostream>
#include <ToDFA.h>
#include <Node.h>
#include <Edge.h>
#include <vector>
#include <Match.h>
#include <Graph.h>
#include "Language_NFA_Generator.h"
#include <FirstGenerator.h>
#include <Parser.h>
#include <Parsing_Table.h>
#include <FollowGenerator.h>
#include <queue>
#include <stack>

using namespace std;


int main()
{
    /*Language_NFA_Generator* language_builder = new Language_NFA_Generator("difinitions.txt");
    Graph* language_graph = language_builder->getNFA();
    unordered_map<char,int> inputs = language_builder->get_input_map();

    ToDFA obj;
    vector<Node*> Nodes;
    Nodes.push_back(language_graph->get_start_node());
    vector<Node*> out;
    out = obj.SubsetConstruction(Nodes,inputs);*/

    /*for (int i=0 ; i<out.size() ; i++)
    {
        cout << "--------------------\n";
        cout<<out[i]->get_node_name()<<" ::::" << out[i]->is_acceptance_node() << ":::: ";
        vector <Edge>& e = *(out[i]->get_children());
        cout << endl ;
        for (int k=0 ; k<e.size() ; k++)
        {
            cout << e[k].get_value() << " " <<  e[k].get_end_node()->get_node_name() << endl;

        }
    }*/

    /*Match * objM = new Match(obj.getPhiState());
    ifstream file("Input.txt");
    string str;
    while (std::getline(file, str))
    {
        objM->match_tokens(out ,str);
    }
    file.close();*/

    /*cout << "========= TOKENS ===========" << endl;
    for (int j=0 ; j<tokens.size() ; j++)
        cout << tokens.at(j) << endl;
    cout << "============================" << endl;*/




    ////////////////////////////////////// Phase 2 //////////////////////////////////////




    //////// Get tokens /////////
    Language_NFA_Generator* language_builder = new Language_NFA_Generator("difinitions.txt");
    Graph* language_graph = language_builder->getNFA();
    unordered_map<char,int> inputs = language_builder->get_input_map();

    ToDFA obj;
    vector<Node*> Nodes;
    Nodes.push_back(language_graph->get_start_node());
    vector<Node*> out;
    out = obj.SubsetConstruction(Nodes,inputs);

    Match * objM = new Match(obj.getPhiState());
    ifstream file("Input2.txt");
    string str;
    while (std::getline(file, str))
    {
        objM->match_tokens(out ,str);
    }
    vector<string> tokens = objM->Return_Tokens();
    file.close();
    ///////////////////////////

    //////// Parse ////////////
    Parser * ph2 = new Parser();

    unordered_map<string,vector<vector<Symbol*> > > Productions_map = ph2->Parse();
    //////////////////////////

    /////// Get first ///////
    FirstGenerator * FG = new FirstGenerator(Productions_map);

    unordered_map<string, vector< string >> first = FG->get_first_set();

    cout <<  "================== Print the first =======================" << endl;
    for (auto it =first.begin() ; it!=first.end() ; ++it)
    {
        cout << it->first << " ::= " ;

        vector<string> vv = it->second ;
        for (int i=0 ; i<vv.size() ; i++)
        {
            cout << vv.at(i) << " " ;
        }
        cout << endl;
    }
    cout <<  "==========================================================" << endl;

    /////////////////////////

    ////// Get follow ///////
    FollowGenerator * FoG = new FollowGenerator(Productions_map,first);

    unordered_map<string, vector< string >> follow = FoG->get_follow_set();

    cout << "================== Print the follow =======================" << endl;
    for (auto it =follow.begin() ; it!=follow.end() ; ++it)
    {
        cout << it->first << " ::= " ;

        vector<string> vv = it->second ;
        for (int i=0 ; i<vv.size() ; i++)
        {
            cout << vv.at(i) << " " ;
        }
        cout << endl;
    }
    cout <<  "==========================================================" << endl;

    ////////////////////////


    /** stack test **/

    /*stack<Symbol*> parser;

    Parsing_Table* pt = new Parsing_Table(first,follow,Productions_map);

    vector<vector<vector<Symbol*>>> table = pt->get_table();

    unordered_map<string , int> terminals = pt->get_terminals_map();
    unordered_map<string , int> nonterminals = pt->get_nonterminals_map();

    Symbol* starting_symbol = pt->get_starting_symbol();


    parser.push(new Symbol("$",false));
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

        else if( top->is_terminal())
        {
            if (top->get_value()!=tokens[index] ){
                cout <<" Error: (missing) poping " << endl;
            }
            else {
                index++;
            }
            parser.pop();
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
                cout << " Error:(illegal) discarding input " << endl;
                index++;
                continue;
            }
        }

        else
        {
            cout << " Error for matching ..... shutting down " << endl;
            break;
            //error
        }


    }*/




    return 0;
}

