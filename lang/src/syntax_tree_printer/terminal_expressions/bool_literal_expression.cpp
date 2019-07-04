#include <iostream>

#include "./terminal_expressions.hpp"

namespace syntax_tree_printer::terminal_expressions
{
    void print_bool_literal_expression(const syntax_tree::terminal_expressions::BoolLiteralExpression & bool_literal_exp, unsigned int indents)
    {
        std::cout << std::string(indents, ' ') << "Bool Literal Expression: " << bool_literal_exp.value() << "\n";
    }
}