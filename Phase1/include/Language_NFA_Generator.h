#ifndef LANGUAGE_NFA_GENERATOR_H
#define LANGUAGE_NFA_GENERATOR_H

#include "GraphBuilder.h"

#include "Graph.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>

#include "unordered_map"

using namespace std;

class Language_NFA_Generator
{
    public:
        Language_NFA_Generator(string file_path);
        Graph* getNFA();
        unordered_map<char,int> get_input_map(){
            return input_map;
        }
        string post_fix_conversion(string exp);
        Graph *evaluate(string expr ,unordered_map <string,Graph*> *graphs);
        bool is_operand(string type);

    protected:
    private:
        string file_path;
        GraphBuilder builder;

        // hold all the builded graphs
        unordered_map<string,Graph*> language_map;

        //hold all inputs
        unordered_map<char,int> input_map;
        int input_count = 0;

        void build_keyword(string line);
        void build_punctuation(string line);
        void build_regular(string line);

        Graph* copy_graph(Graph *g);
        Graph* build_new_input_graph(string temp_string );
        Graph *get_language_graph();

        stack <string> operand;
        stack <string> operation;

};

#endif // NFA_GENERATOR_H
