#include <iostream>

#include "./terminal_expressions.hpp"

namespace syntax_tree_printer::terminal_expressions
{
    void print_string_literal_expression(const syntax_tree::terminal_expressions::StringLiteralExpression & string_literal_exp, unsigned int indents)
    {
        std::cout << std::string(indents, ' ') << "String Literal Expression: \"" << string_literal_exp.string_text() << "\"\n";
    }
}