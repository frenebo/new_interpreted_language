#include <iostream>
#include "./statements.hpp"
#include "../compound_expression/compound_expression.hpp"
#include "../statement_series/statement_series.hpp"

namespace syntax_tree_printer::statements
{
    void print_if_statement(const syntax_tree::statements::IfStatement & statement, unsigned int indents)
    {
        std::cout << std::string(' ', indents) << "If Statement:\n";
        
        std::cout << std::string(' ', indents + 1) << "Condition:\n";
        syntax_tree_printer::compound_expression::print_compound_expression(statement.if_condition(), indents + 2);

        std::cout << std::string(' ', indents + 1) << "If Body:\n";
        syntax_tree_printer::statement_series::print_statement_series(statement.body_statement_series(), indents + 2);
    }
}