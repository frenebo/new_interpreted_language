#include <iostream>

#include "./statements.hpp"
#include "../compound_expression/compound_expression.hpp"

namespace syntax_tree_printer::statements
{
    void print_print_statement(const syntax_tree::statements::PrintStatement & print_statement, unsigned int indents)
    {
        std::cout << std::string(indents, ' ') << "Print statement:\n";

        syntax_tree_printer::compound_expression::print_compound_expression(print_statement.exp_to_print(), indents + 1);
    }
}
