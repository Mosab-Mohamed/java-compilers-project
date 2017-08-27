#include "Parsing_Table.h"

Parsing_Table::Parsing_Table(unordered_map<string , vector<string>> first,
                              unordered_map<string , vector<string>> follow,
                              unordered_map< string,vector< vector<Symbol*> > > productions_set)
{
    this->first_set = first ;
    this->follow_set = follow ;
    this->productions = productions_set;
}

vector<vector<vector<Symbol*>>> Parsing_Table::get_table()
{
    /**
        initializing table
    **/
    set_nonterminals();
    set_terminals();
    vector<vector<vector<Symbol*>>> table( nonterminal_size,vector<vector<Symbol*>>( terminal_size,vector<Symbol*>() ) );

    /*set_nonterminals();
    set_terminals();
    unordered_map< string,vector<Symbol*> > map1;
    map1.reserve(terminal_size);

    unordered_map<unordered_map< string,vector<Symbol*>>> map2;
    map2.reserve(nonterminal_size);

    for( auto it = terminals_map.begin(); it != terminals_map.end(); ++it )
    {
        map1.insert( pair<string,vector<Symbol*>>(it->first,vector<Symbol*>( terminal_size,new Symbol("") )) );
    }

    vector< unordered_map< string,vector<Symbol*> > > table1 (nonterminal_size, map1);
    vector<vector<Symbol*>> tab2(nonterminal_size,vector<Symbol*>(terminal_size,new Symbol("error")));*/

    for( auto it1 = productions.begin(); it1 != productions.end(); ++it1 )  //for each production (i.e Alpha)
    {
        /** outer vector to separate productions in case of | (i.e A -> ab | cd | f)**/
        vector< vector<Symbol*> > non_terminal = it1->second ;   //R.H.S of a production
        string non_terminal_name = it1->first ;                 //L.H.S of a production (i.e non-terminal name)

        for( vector<Symbol*> it2 : non_terminal ) //for each and case in the R.H.S of a production
        {
            if(it2.size()>0)
            {
                cout<<non_terminal_name<<":\n";
                Symbol* first_symbol = it2.front();
                cout<<"first symbo value is : "<<first_symbol->get_value()<<":\n";
                if( first_set.find(first_symbol->get_value()) != first_set.end() )
                {
                    /** first set of the fisrt symbol in the R.H.S production vector **/
                    vector<string> symbol_first_set = first_set.find(first_symbol->get_value())->second;

                    for( string first_it : symbol_first_set ) // iterate over first set
                    {
                        //if the value in the first set equals \L
                        if(first_it=="\\L")
                        {
                            cout<<"enter epsilon from "<<non_terminal_name<<"\n";
                            if( follow_set.find(non_terminal_name) != follow_set.end() )
                            {
                                /** follow set of the L.H.S of a production **/
                                vector<string> symbol_follow_set = follow_set.find(non_terminal_name)->second;

                                for( string follow_it : symbol_follow_set ) // iterate over follow set
                                {
                                    cout<<follow_it;

                                    table[ nonterminals_map.find(non_terminal_name)->second ][ terminals_map.find(follow_it)->second ] = it2 ;
                                    /*
                                    if( table.find(non_terminal_name) == table.end() )
                                    {
                                        vector< unordered_map< string,vector<Symbol*> > > vv ;
                                        unordered_map< string,vector<Symbol*> > terminal_symbol;
                                        terminal_symbol.insert(pair< string,vector<Symbol*> >(follow_it,it2));
                                        vv.push_back(terminal_symbol);
                                        table.insert(pair<string, vector< unordered_map< string,vector<Symbol*> > > >(non_terminal_name, vv));
                                    }
                                    else
                                    {
                                        cout<<"===== "<<non_terminal_name<<" , "<<follow_it<<" ======\n";
                                        vector< unordered_map< string,vector<Symbol*> > > vvv  = table.find(non_terminal_name)->second;
                                         unordered_map< string,vector<Symbol*> > terminal_symbol ;

                                        for( unordered_map< string,vector<Symbol*> > terminal : vvv )
                                        {
                                            for( auto it9 = terminal.begin(); it9 != terminal.end(); ++it9 )
                                            {

                                                cout<<"[ "<<non_terminal_name<<" , "<<it9->first<<" ]\n";
                                            }


                                        }

                                        terminal_symbol.insert(pair< string,vector<Symbol*> >(follow_it,it2));
                                        vvv.push_back(terminal_symbol);
                                        table.insert(pair<string, vector< unordered_map< string,vector<Symbol*> > > >(non_terminal_name, vvv));



                                    }
                                    */

                                }

                            }

                            else
                            {
                                cout<<"no follow set for "<<non_terminal_name<<"\n";
                            }


                        }

                        //if the value in the first set doesn't equal \L
                        else
                        {
                            cout<<"first_it is "<<first_it<<"\n";
                            table[ nonterminals_map.find(non_terminal_name)->second ][ terminals_map.find(first_it)->second ] = it2 ;
                            /*
                            if( table.find(non_terminal_name) == table.end() )
                            {
                                vector< unordered_map< string,vector<Symbol*> > > vv ;
                                unordered_map< string,vector<Symbol*> > terminal_symbol;
                                terminal_symbol.insert(pair< string,vector<Symbol*> >(first_it,it2));
                                vv.push_back(terminal_symbol);
                                table.insert(pair<string, vector< unordered_map< string,vector<Symbol*> > > >(non_terminal_name, vv));
                            }
                            else
                            {
                                cout<<"===== "<<non_terminal_name<<" , "<<first_it<<" ======\n";
                                vector< unordered_map< string,vector<Symbol*> > > vvv  = table.find(non_terminal_name)->second;
                                unordered_map< string,vector<Symbol*> > terminal_symbol ;
                                terminal_symbol.insert(pair< string,vector<Symbol*> >(first_it,it2));
                                vvv.push_back(terminal_symbol);
                            }
                            */
                        }




                    }
                    cout<<"\n\n";


                }
                else
                {
                    cout<<"no first set for "<<first_symbol->get_value()<<"\n";
                }


            }



        }



    }

    return table;
}


void Parsing_Table::set_nonterminals()
{
    for( auto it1 = productions.begin(); it1 != productions.end(); ++it1 )  //for each production (i.e Alpha)
    {

        nonterminals_map.insert(pair<string,int>(it1->first,nonterminal_size++));
        if(nonterminal_size==productions.size())
        {
            this->starting_symbol = new Symbol(it1->first) ;
        }
    }
}


void Parsing_Table::set_terminals()
{
    for( auto it1 = productions.begin(); it1 != productions.end(); ++it1 )  //for each production (i.e Alpha)
    {
        for( vector<Symbol*> it2 : it1->second )
        {
            for( Symbol* ss : it2 )
            {
                if(nonterminals_map.find(ss->get_value()) == nonterminals_map.end())
                {
                    terminals_map.insert(pair<string,int>(ss->get_value(),terminal_size++));
                }
            }
        }
    }

    terminals_map.insert(pair<string,int>("$",terminal_size++));
}

unordered_map<string , int> Parsing_Table::get_terminals_map()
{
    return terminals_map;
}

unordered_map<string , int> Parsing_Table::get_nonterminals_map()
{
    return nonterminals_map;
}

Symbol* Parsing_Table::get_starting_symbol()
{
    return starting_symbol;
}
