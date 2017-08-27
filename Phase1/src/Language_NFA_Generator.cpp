#include "Language_NFA_Generator.h"
#include "strings.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include<queue>

Language_NFA_Generator::Language_NFA_Generator(string file_path)
{
    //ctor
    this->file_path = file_path;
}

string Language_NFA_Generator::post_fix_conversion(string exp)
{
    char expr[exp.length()];
    string element="";
    int i=0;
    strcpy(expr, exp.c_str());
    while(i<exp.length())
    {
        if((string(1 , exp[i])!="*")&&
                (string(1 , exp[i])!="+")&&
                (string(1 , exp[i])!=".")&&
                (string(1 , exp[i])!="|")&&
                (string(1 , exp[i])!="(")&&
                (string(1 , exp[i])!=")"))
        {
//input is operand
            operand.push(string(1 , exp[i]));

            i++;
        }
        else
//input is operation
            if((string(1 , exp[i])=="*")||
                    (string(1 , exp[i])=="+")||
                    (string(1 , exp[i])=="("))
            {
                if(string(1 , exp[i])=="(")
                {
                    operation.push(string(1 , exp[i]));
                    i++;
                }
                else
                {
                    operation.push(string(1 , exp[i]));
                    i++;
                }
            }
            else if(string(1 , exp[i])==".")
            {
                if(operation.empty())
                {
                    operation.push(string(1 , exp[i]));
                    i++;
                }
                else
                {
                    if((operation.top()=="*")||(operation.top()=="+"))
                    {
                        element=element +""+operand.top();
                        element=element +""+operation.top();
                        operand.pop();
                        operation.pop();
                        operand.push (element);
                        operation.push (string(1 , exp[i]));
                        element="";
                        i++;
                    }
                    else
                    {
                        operation.push (string(1 , exp[i]));
                        i++;
                    }
                }

            }
            else if(expr[i]=='|')
            {
                if(operation.empty())
                {
                    operation.push(string(1 , exp[i]));
                    i++;
                }
                else
                {
                    if((operation.top()=="*")||(operation.top()=="+"))
                    {

                        element=element +""+operand.top();
                        element=element +""+operation.top();
                        operand.pop();
                        operation.pop();
                        operand.push(element);
                        operation.push(string(1 , exp[i]));
                        element="";
                        i++;
                    }
                    else if ((operation.top()=="."))
                    {
                        element=element +""+operand.top();

                        operand.pop();
                        element=element +""+operand.top();
                        operand.pop();
                        element=element +""+operation.top();
                        operation.pop();
                        operand.push(element);
                        operation.push(string(1 , exp[i]));
                        element="";
                        i++;
                    }
                    else
                    {
                        operation.push(string(1 , exp[i]));
                        i++;
                    }
                }
            }
            else if(string(1 , exp[i])==")")
            {
                if(operation.empty())
                {
                    cout<<"ERROR IN EXP";
                }
                while((operation.top()!="(")&&(!operation.empty())&& (!operand.empty()))
                {
                    if ((operation.top()=="*")||(operation.top()=="+"))
                    {
                        element ="";
                        element=element+""+operand.top()+""+operation.top();
                        operation.pop();
                        operand.pop();
                        operand.push(element);
                        element="";
                    }
                    else if((operation.top()=="|")||(operation.top()=="."))
                    {
                        element=element+""+operand.top();
                        operand.pop();
                        element=element+""+operand.top();
                        element=element+""+operation.top();
                        operand.pop();
                        operation.pop();
                        operand.push(element);
                        element="";
                    }

                }

                operation.pop();
                i++;
            }
    }
    if(operand.empty())
    {
        return NULL;
    }
    if(operation.empty())
    {
        element=operand.top();
        operand.pop();
    }
    else
    {

        while(!operand.empty()&&(!operation.empty()))
        {
            if ((operation.top()=="*")||(operation.top()=="+"))
            {
                element ="";
                element=element+""+operand.top()+""+operation.top();
                operation.pop();
                operand.pop();
                operand.push(element);
                element="";
            }
            else if((operation.top()=="|")||(operation.top()=="."))
            {
                element=element+""+operand.top();
                operand.pop();
                element=element+""+operand.top();
                element=element+""+operation.top();
                operand.pop();
                operation.pop();
                operand.push(element);
                element="";
            }
        }
        element=operand.top();
        while(!operation.empty())
        {
            element=element+""+operation.top();
            operation.pop();


        }

    }
    return element;
}

Graph *Language_NFA_Generator::evaluate(string expr,unordered_map <string,Graph*> *graphs)
{
    string post_fix=post_fix_conversion(expr);
    unordered_map<string,Graph*>::const_iterator itr;
    Graph* g1,*g2;
    char expr_array[post_fix.length()];
    string element="";
    int i=0;
    strcpy(expr_array, post_fix.c_str());
    //stack <string> operationS;
    stack<Graph *> operandG;
    for(i=0; i<post_fix.length(); i++)
    {
        if((string(1 , expr_array[i])!="*")&&
                (string(1 , expr_array[i])!="+")&&
                (string(1 , expr_array[i])!=".")&&
                (string(1 , expr_array[i])!="|"))
        {
            itr=graphs->find(string(1,expr_array[i]));
            operandG.push(itr->second);
        }
        else
        {   //operationS.push(string(1 , expr_array[i]));
            if((string(1 , expr_array[i])=="*"))
            {
                g1=operandG.top();
                operandG.pop();
                operandG.push(builder.clousure_operation(g1));
            }
            else if((string(1 , expr_array[i])=="+"))
            {
                g1=operandG.top();
                operandG.pop();
                operandG.push(builder.positive_clousure_operation(g1));
            }
            else if((string(1 , expr_array[i])=="."))
            {
                g1=operandG.top();
                operandG.pop();
                g2=operandG.top();
                operandG.pop();
                operandG.push(builder.and_operation(g1,g2));

            }
            else if((string(1 , expr_array[i])=="|"))
            {

                g1=operandG.top();
                operandG.pop();
                g2=operandG.top();
                operandG.pop();
                operandG.push(builder.or_operation(g1,g2));
            }

        }


    }

    return operandG.top();

}

Graph* Language_NFA_Generator::getNFA()
{

    ifstream grammar_file (file_path.c_str());
    string line;

    // Check if file opened
    if (grammar_file.is_open())
    {

        //read file line by line
        while ( getline (grammar_file,line) )
        {
            //cout << line << endl;

            if( line.empty() || line[0] == ' '|| line[0] == '\t') // Empty line or white space
                continue;

            else if( line[0] == '{') // Key words
                build_keyword(line);

            else if(line[0] == '[') // punctuation
                build_punctuation(line);

            else // Regular Expression or Definition
                build_regular(line);

        }

        grammar_file.close();
        return get_language_graph();
    }
    else   // Error in opening file
    {
        cout << "Failed to open file";
        return NULL;
    }

}

/**
*   Read keyword  line from grammerfile and build its graph
*/
void Language_NFA_Generator::build_keyword(string line)
{
    Graph *temp_graph = NULL;
    string temp_string = "" ;

    // move on the line and construct a graph for each key word
    for(int i = 1 ; i < line.length() ; i++)
    {

        if(line[i] == ' '|| line[i] == '\t')  // white space
        {
            if( temp_graph == NULL ) // White space in the begining of the line like "{ int....}"
                continue;

            // Set last node as acceptance state
            temp_graph->get_end_node()->set_acceptance_state(true);
            temp_graph->get_end_node()->set_token_type("key word");
            temp_graph->get_end_node()->set_token(temp_string);

            if( language_map.find("key_word") != language_map.end() )
            {

                //There is already graph for key words so update the graph only
                Graph *old_graph = language_map.find("key_word")->second;
                language_map["key_word"] = builder.or_operation(old_graph,temp_graph);

            }
            else  // Add new key word key
                language_map.insert(pair<string,Graph*>("key_word", temp_graph));

            temp_graph = NULL; // To start new graph
            temp_string = "" ;
        }
        else if( line[i] == '}')   // end of key words
        {
            if( temp_graph == NULL)
                break;

            // Set last node as acceptance state
            temp_graph->get_end_node()->set_acceptance_state(true);
            temp_graph->get_end_node()->set_token_type("key word");
            temp_graph->get_end_node()->set_token(temp_string);

            if( language_map.find("key_word") != language_map.end() )
            {

                //There is already graph for key words so update the graph only
                Graph *old_graph = language_map.find("key_word")->second;
                language_map["key_word"] =  builder.or_operation(old_graph,temp_graph);

            }
            else  // Add new
                language_map.insert(pair<string,Graph*>("key_word", temp_graph));
            temp_graph = NULL;
            temp_string = "" ;
            break;
        }
        /*if(line[i] == ' ' || line[i] == '\t' || line[i] == '}' )  // white space
        {
            if( temp_graph == NULL ) // White space in the begining of the line like "{ int....}"
            {
                if(line[i] == '}')
                    break;
                else
                    continue;
            }


            // Set last node as acceptance state
            temp_graph->get_end_node()->set_acceptance_state(true);
            temp_graph->get_end_node()->set_token_type("key word");


            if( language_map.find("key_word") != language_map.end() )//find a graph with this key
            {

                //There is already graph for key words so update the graph only
                Graph *old_graph = language_map.find("key_word")->second;   // the mapped value (the graph that "key word" map to)
                language_map["key_word"] = builder.or_operation(old_graph,temp_graph);

            }
            else  // Add new key word key
                language_map.insert(pair<string,Graph*>("key_word", temp_graph));


            temp_graph = NULL; // To start new graph

            if(line[i] == '}')
                    break;

        }*/
        /***********************/

        /*************************/
        else   // character
        {
            if( input_map.find(line[i]) == input_map.end() ) // this character not added before
                input_map.insert(pair<char,int>(line[i], input_count++)); // Add new character to input map

            if( temp_graph == NULL )// Build graph for first charachter
            {
                temp_string += string(1,line[i]) ;
                temp_graph = builder.init_graph(string(1,line[i]));
            }
            else // concatenate old graph and new graph of the new character
            {
                temp_string += string(1,line[i]) ;
                temp_graph = builder.and_operation(temp_graph , builder.init_graph(string(1,line[i])));
            }
        }

    }

    delete temp_graph;
}

/**
*   Read paunctuation line from grammerfile and build its graph
*/
void Language_NFA_Generator::build_punctuation(string line)
{
    Graph * temp_graph = NULL;
    string temp_string = "" ;

    // move on the line and construct a graph for each punctuation
    for(int i = 1 ; i < line.length() ; i++)
    {
        if(line[i] == ' '|| line[i] == '\t') // white space
            continue;

        else if( line[i] == ']') // end of punctuations
            break;

        else  // punctiation
        {

            if( line[i] == 92 /* '\'*/ && i+1 < line.length() && ( line[i+1] == ')' || line[i+1] == '(' ) ) //case \( or \)
            {
                temp_graph = builder.init_graph(string(1,line[i+1]));
                temp_string +=string(1,line[i+1]);
                i++; //skip ) or (
            }
            else
            {
                temp_string +=string(1,line[i]);
                temp_graph = builder.init_graph(string(1,line[i]));
            }


            // Set last node as acceptance state
            temp_graph->get_end_node()->set_acceptance_state(true);
            temp_graph->get_end_node()->set_token_type("punctuation");
            temp_graph->get_end_node()->set_token(temp_string);

            // Add new character to input map
            if( input_map.find(line[i]) == input_map.end() ) // this character not added before
                input_map.insert(pair<char,int>(line[i], input_count++));

            if( language_map.find("punctuation") != language_map.end() )
            {
                //There is already graph for punctuations so update the graph only

                Graph *old_graph = language_map.find("punctuation")->second;
                language_map["punctuation"] = builder.or_operation(old_graph, temp_graph);

            }
            else  // Add new
                language_map.insert(pair<string,Graph*>("punctuation", temp_graph));

            temp_graph = NULL;
            temp_string = "" ;
        }
    }

    delete temp_graph;
}

/**
*   Read Regular expression or deffinition line from grammerfile and build its graph
*/
void Language_NFA_Generator::build_regular(string line)
{
    string exp_name;
    int i = 0;

    // skip white spaces in the beggining of the file
    while(i < line.length() && (line[i] == ' ' || line[i] == '\t') )
        i++;

    //build exp_name
    while(i < line.length() && line[i] != ' ' && line[i] != '\t' && line[i] !='=' && line[i] != ':' )
        exp_name = string(exp_name + line[i++]);

    // skip white spaces after exp name
    while(i < line.length() && (line[i] == ' ' || line[i] == '\t') )
        i++;

    if( i < line.length() && (line[i] == '='|| line[i] == ':' ))
    {
        unordered_map<string, Graph*> exp_graphs;
        stringstream exp_string;
        stringstream temp_string;
        char index_char = 'a';

        for(i=i+1 ; i < line.length() ; i++ )
        {
            if( line[i] == ' ' || line[i] == '\t' ) //the delimeter between exp components
            {
                if( temp_string.str().empty() ) // Spaces
                    continue;

                Graph* temp_graph = build_new_input_graph(temp_string.str()); //return the graph that temp_string refers to or NULL in case of error

                if( temp_graph == NULL )//Error
                    return ;

                // create new graph
                exp_graphs.insert(pair<string,Graph*>( string(1,index_char), temp_graph ));
                // Add the chosen char to the expression to be user in evaluation
                exp_string << index_char;
                index_char++;

                temp_string.clear();
                temp_string.str("");

                temp_graph = NULL;
                delete temp_graph;
            }
            else if( temp_string.str() != "\\"&& ( line[i] == '+' || line[i] == '*' || line[i] == '|' || line[i] == '.' || line[i] == '(' || line[i] == ')' ) )  // Operation
            {
                if( !temp_string.str().empty() )
                {

                    Graph* temp_graph = build_new_input_graph(temp_string.str());
                    if( temp_graph == NULL )//Error
                        return ;

                    // create new graph
                    exp_graphs.insert(pair<string,Graph*>( string(1,index_char), temp_graph ));
                    // Add the chosen char to the expression to be user in evaluation
                    exp_string << index_char <<  line[i];
                    index_char++;

                    temp_string.clear();
                    temp_string.str("");


                    temp_graph = NULL;
                    delete temp_graph;
                }
                else
                    exp_string <<  line[i] ;


            }
            else // append character to temp_string to be used as name of key of the map
                temp_string<< line[i];
        }

        if( !temp_string.str().empty() )
        {

            Graph* temp_graph = build_new_input_graph(temp_string.str());
            if( temp_graph == NULL )//Error
                return ;

            exp_graphs.insert(pair<string,Graph*>( string(1,index_char), temp_graph ));
            // Add the chosen char to the expression to be user in evaluation
            exp_string << index_char;
            index_char++;

            temp_string.clear();
            temp_string.str("");


            temp_graph = NULL;
            delete temp_graph;
        }

        //Evaluate the expression
        Graph* result_graph = evaluate(exp_string.str() , &exp_graphs);
        result_graph->get_end_node()->set_acceptance_state(true);
        result_graph->get_end_node()->set_token_type(exp_name);

        // insert new reg expression or deffinition
        language_map.insert(pair<string,Graph*>(exp_name, result_graph));

        result_graph = NULL;
        delete result_graph;
    }
    else
        cout<< "Grammar Error!" << endl;
}


/** take a string and found if it is a expression definition that already have graph or build new graph for it  **/
Graph * Language_NFA_Generator::build_new_input_graph(string temp_string)
{
    Graph *temp_graph;
    if( language_map.find(temp_string) != language_map.end())
    {
        /** found predefined expression that has a graph **/
        temp_graph = copy_graph(language_map.find(temp_string)->second);
    }
    else   // New input
    {
        //cout<< temp_string.length() << endl;
        if( temp_string.length() > 1)
        {
            /**
            *   1- Range e.g a-z or 1-9
            *   2- Add or Multiply operation e.g \+ or \*
            *   3- Relational operation e.g \=\= or !\= or > or >\= or < or <\=
            **/
            int i = 0;
            if( temp_string[i] == '\\' || temp_string[i] == '!' ||
                    temp_string[i] == '>' || temp_string[i] == '<')  //case 2 or 3
            {

                if( temp_string[i] == '\\')
                    i++;

                if( input_map.find(temp_string[i]) == input_map.end() ) // this character not added before
                    input_map.insert(pair<char,int>(temp_string[i], input_count++));

                temp_graph = builder.init_graph(string(1,temp_string[i++]));

                for( ; i < temp_string.length() ; i++ )
                {
                    if( temp_string[i] != '\\')
                    {
                        if( input_map.find(temp_string[i]) == input_map.end() ) // this character not added before
                            input_map.insert(pair<char,int>(temp_string[i], input_count++));

                        temp_graph = builder.and_operation(temp_graph , builder.init_graph(string(1,temp_string[i])));
                    }
                }
            }
            else  //Case 1 or error
            {
                char c = temp_string[i];
                temp_graph = builder.init_graph(string(1,temp_string[i++]));

                if( input_map.find(c) == input_map.end() ) // this character not added before
                    input_map.insert(pair<char,int>(c, input_count++));
                c++;

                // skip white spaces after exp name
                while(i < temp_string.length() && (temp_string[i] == ' ' || temp_string[i] == '\t') )
                    i++;

                if( temp_string[i++] != '-')
                {
                    cout<< "Error in Grammar!" <<endl;
                    return NULL;
                }

                // skip white spaces after exp name
                while(i < temp_string.length() && (temp_string[i] == ' ' || temp_string[i] == '\t') )
                    i++;

                for(  ; c <= temp_string[i] ; c++ )  // Range a-z OR 1-9
                {
                    if( input_map.find(c) == input_map.end() ) // this character not added before
                        input_map.insert(pair<char,int>(c, input_count++));

                    temp_graph = builder.or_operation(temp_graph , builder.init_graph(string(1, c)));
                }
            }

        }
        else   // one char
        {
            if( input_map.find(temp_string[0]) == input_map.end() ) // this character not added before
                input_map.insert(pair<char,int>(temp_string[0], input_count++));
            temp_graph = builder.init_graph(temp_string);
        }
    }
    return temp_graph;
}

Graph *Language_NFA_Generator::get_language_graph()
{
    Graph * language_graph;

    unordered_map<string,Graph*>::const_iterator it = language_map.begin();

    if( it == language_map.end() ) // No graphs has been built!
        return NULL;

    language_graph = it->second;
    it++;
    for ( ; it != language_map.end(); ++it )
    {
        language_graph = builder.or_operation(language_graph , it->second);
    }

    return language_graph;
}

Graph* Language_NFA_Generator::copy_graph(Graph *g)
{
    queue <Node*> q;

    // map of key = node name and value pointer to Node in the new graph
    // if there was a value for the givven node name
    unordered_map<int,Node*> node_holder;
    Graph *new_graph = new Graph();

    // Node of old graph
    Node* temp_node;
    // Children of old graph
    vector<Edge> *children;

    // Node of new graph
    Node *new_temp_node;

    temp_node = g->get_start_node();

    // New start Node
    new_temp_node = new Node();
    new_temp_node->set_node_name();

    new_temp_node->set_acceptance_state(temp_node->is_acceptance_node());
    new_temp_node->set_token_type(temp_node->get_token_type());

    //Set start node of new graph
    new_graph->set_start_node(new_temp_node);

    //Push first node
    q.push(temp_node);
    node_holder.insert(pair<int,Node*>(temp_node->get_node_name(), new_temp_node));

    while(q.size()!=0)
    {
        temp_node = q.front(); // old node
        q.pop();

        new_temp_node = node_holder[temp_node->get_node_name()]; // new graph

        children = temp_node->get_children();
        Node * node;

        for(int i=0; i< children->size(); i++)
        {
            node = (*children)[i].get_end_node(); // children #i

            if( node_holder.find(node->get_node_name()) != node_holder.end() ){ // visited add to new graph only
                new_temp_node->add_child( node_holder[node->get_node_name()] , (*children)[i].get_value());
                continue;
            }

            Node *new_node = new Node();
            new_node->set_node_name();

            new_node->set_acceptance_state(node->is_acceptance_node());
            new_node->set_token_type(node->get_token_type());

            new_temp_node->add_child( new_node , (*children)[i].get_value());

            //Not visited
            q.push(node);
            node_holder.insert(pair<int,Node*>((*children)[i].get_end_node()->get_node_name(), new_node));
        }
    }
    // Set end node
    new_graph->set_end_node(node_holder[g->get_end_node()->get_node_name()]);
    new_graph->get_end_node()->set_acceptance_state(g->get_end_node()->is_acceptance_node());
    new_graph->get_end_node()->set_token_type(g->get_end_node()->get_token_type());

    new_graph->set_graph_size(g->get_graph_size());

    return new_graph;
}
