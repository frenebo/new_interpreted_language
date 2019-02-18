#ifndef SYNTAX_TREE_PRINTER_COMPOUND_EXPRESSIONS
#define SYNTAX_TREE_PRINTER_COMPOUND_EXPRESSIONS

#include "../../syntax_tree/compound_expression/compound_expression.hpp"

namespace syntax_tree_printer::compound_expression
{
    void print_compound_expression(const syntax_tree::compound_expression::CompoundExpression & compound_exp, unsigned int indents);
}

#endif
