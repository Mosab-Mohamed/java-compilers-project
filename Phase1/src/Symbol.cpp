#include "Symbol.h"

Symbol::Symbol(string symbol_value,bool is_Terminal)
{
    this->value = symbol_value;
    is_terminal_symbol = is_Terminal;
}

bool Symbol::is_terminal(){
    return is_terminal_symbol;
}

string Symbol::get_value(){
    return value;
}
