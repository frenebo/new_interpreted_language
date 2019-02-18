#ifndef SYNTAX_TREE_PRINTER_STATEMENT
#define SYNTAX_TREE_PRINTER_STATEMENT

#include "../../syntax_tree/statements/statements.hpp"

namespace syntax_tree_printer::statements
{
    void print_compound_expression_statement(const syntax_tree::statements::CompoundExpressionStatement & compound_exp_statement, unsigned int indents);
    void print_statement_container(const syntax_tree::statements::StatementContainer &, unsigned int indents);
}

#endif
