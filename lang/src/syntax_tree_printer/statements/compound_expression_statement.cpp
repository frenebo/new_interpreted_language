#include <iostream>
#include "./statements.hpp"
#include "../compound_expression/compound_expression.hpp"

namespace syntax_tree_printer::statements
{
    void print_compound_expression_statement(const syntax_tree::statements::CompoundExpressionStatement & compound_exp_statement, unsigned int indents)
    {
        std::cout << std::string(indents, ' ') << "Compound Expression Statement:\n";

        syntax_tree_printer::compound_expression::print_compound_expression(compound_exp_statement.compound_exp(), indents + 1);
    }
}