#ifndef SYMBOL_H
#define SYMBOL_H
#include<string>

using namespace std ;

class Symbol
{
    public:
        Symbol(string);
        bool is_terminal();
        string get_value();
        void set_terminal(bool);
    protected:
    private:
        string value;
        bool is_terminal_symbol = false;
};

#endif // SYMBOL_H
