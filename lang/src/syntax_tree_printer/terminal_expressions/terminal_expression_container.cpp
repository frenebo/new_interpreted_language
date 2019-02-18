#include <iostream>
#include "./terminal_expressions.hpp"

namespace syntax_tree_printer::terminal_expressions
{
    void print_terminal_expression_container(const syntax_tree::terminal_expressions::TerminalExpressionContainer & terminal_exp_container, unsigned int indents)
    {
        auto contained = terminal_exp_container.contained_terminal_exp();
        if (std::holds_alternative<syntax_tree::terminal_expressions::IdentifierExpression>(contained))
        {
            print_identifier_expression(std::get<syntax_tree::terminal_expressions::IdentifierExpression>(contained), indents);
        }
        else if (std::holds_alternative<syntax_tree::terminal_expressions::NumberExpression>(contained))
        {
            print_number_expression(std::get<syntax_tree::terminal_expressions::NumberExpression>(contained), indents);
        }
        else
        {
            std::cout << std::string(indents, ' ') << "Unimplemented terminal print\n";
        }
    }
}