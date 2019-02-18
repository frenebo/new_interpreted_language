#include <iostream>
#include "./compound_expression.hpp"
#include "../terminal_expressions/terminal_expressions.hpp"

namespace syntax_tree_printer::compound_expression
{
    void print_possibly_prefixed_terminal(const syntax_tree::compound_expression::PossiblyPrefixedTerminal & possibly_prefixed_terminal, unsigned int indents)
    {
        if (possibly_prefixed_terminal.possible_prefix_type().has_value())
        {
            std::cout << std::string(indents, ' ') << "Prefixed Terminal\n";

            syntax_tree::compound_expression::PrefixType prefix_type =
                *possibly_prefixed_terminal.possible_prefix_type();

            // print prefix type
            if (prefix_type == syntax_tree::compound_expression::PrefixType::MINUS_PREFIX)
            {
                std::cout << std::string(indents + 1, ' ') << "Minus Prefix\n";
            }
            else
            {
                std::cout << std::string(indents + 1, ' ') << "Unimplemented prefix print\n";
            }

            syntax_tree_printer::terminal_expressions::print_terminal_expression_container(possibly_prefixed_terminal.terminal_exp_container(), indents + 1);
        }
        else
        {
            syntax_tree_printer::terminal_expressions::print_terminal_expression_container(possibly_prefixed_terminal.terminal_exp_container(), indents);
        }
    }
}