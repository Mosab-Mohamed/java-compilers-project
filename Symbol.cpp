#include "Symbol.h"

Symbol::Symbol(string symbol_value)
{
    this->value = symbol_value;
}

bool Symbol::is_terminal(){
    return is_terminal_symbol;
}

void Symbol::set_terminal(bool t){
    is_terminal_symbol = t;
}

string Symbol::get_value(){
    return value;
}
