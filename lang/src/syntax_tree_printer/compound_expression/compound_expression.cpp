#include <iostream>

#include "./compound_expression.hpp"

namespace syntax_tree_printer::compound_expression
{
    void print_compound_expression(const syntax_tree::compound_expression::CompoundExpression & compound_exp, unsigned int indents)
    {
        std::cout << std::string(indents, ' ') << "Compound Expression: \n";

        // compound_exp.
    }
}