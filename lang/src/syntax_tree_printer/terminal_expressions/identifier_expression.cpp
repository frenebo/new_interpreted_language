#include <iostream>
#include "./terminal_expressions.hpp"

namespace syntax_tree_printer::terminal_expressions
{
    void print_identifier_expression(const syntax_tree::terminal_expressions::IdentifierExpression & identifier_exp, unsigned int indents)
    {
        std::cout << std::string(indents, ' ') << "Identifier \"" + identifier_exp.identifier_string() + "\"\n";
    }
}
