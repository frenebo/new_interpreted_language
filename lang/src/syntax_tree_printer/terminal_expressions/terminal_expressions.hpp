#ifndef SYNTAX_TREE_PRINTER_TERMINAL_EXPRESSIONS
#define SYNTAX_TREE_PRINTER_TERMINAL_EXPRESSIONS

#include "../../syntax_tree/terminal_expressions/terminal_expressions.hpp"

namespace syntax_tree_printer::terminal_expressions
{
    void print_terminal_expression_container(const syntax_tree::terminal_expressions::TerminalExpressionContainer & terminal_exp_container, unsigned int indents);

    void print_identifier_expression(const syntax_tree::terminal_expressions::IdentifierExpression & identifier_exp, unsigned int indents);

    void print_number_expression(const syntax_tree::terminal_expressions::NumberExpression & number_exp, unsigned int indents);

    void print_bool_literal_expression(const syntax_tree::terminal_expressions::BoolLiteralExpression & bool_literal_exp, unsigned int indents);
}

#endif
