#ifndef SYMBOL_H
#define SYMBOL_H
#include <string>
using namespace std;

class Symbol
{
    public:
        Symbol(string,bool);
        bool is_terminal();
        string get_value();
    protected:
    private:
        string value;
        bool is_terminal_symbol = false;
};

#endif // SYMBOL_H
