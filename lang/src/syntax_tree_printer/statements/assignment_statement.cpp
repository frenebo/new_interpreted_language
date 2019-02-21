#include <iostream>

#include "./statements.hpp"
#include "../compound_expression/compound_expression.hpp"

namespace syntax_tree_printer::statements
{
    void print_assignment_statement(const syntax_tree::statements::AssignmentStatement & statement, unsigned int indents)
    {
        std::cout << std::string(' ', indents) << "Assignment statement (var name \"" + statement.var_name() + "\"):\n";

        syntax_tree_printer::compound_expression::print_compound_expression(statement.assigned_exp(), indents + 1);
    }
}