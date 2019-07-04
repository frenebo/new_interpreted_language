#include <iostream>
#include "./statements.hpp"

namespace syntax_tree_printer::statements
{
    void print_statement_container(const syntax_tree::statements::StatementContainer & statement_container, unsigned int indents)
    {
        // std::cout << std::string(indents, ' ') << "Statement Container: ";

        auto contained = statement_container.contained_statement();
        if (std::holds_alternative<syntax_tree::statements::CompoundExpressionStatement>(contained))
        {
            print_compound_expression_statement(
                std::get<syntax_tree::statements::CompoundExpressionStatement>(contained),
                indents
            );
        }
        else if (std::holds_alternative<syntax_tree::statements::PrintStatement>(contained))
        {
            print_print_statement(
                std::get<syntax_tree::statements::PrintStatement>(contained),
                indents
            );
        }
        else if (std::holds_alternative<syntax_tree::statements::IfStatement>(contained))
        {
            print_if_statement(
                std::get<syntax_tree::statements::IfStatement>(contained),
                indents
            );
        }
        else if (std::holds_alternative<syntax_tree::statements::ForLoopStatement>(contained))
        {
            print_for_loop_statement(
                std::get<syntax_tree::statements::ForLoopStatement>(contained),
                indents
            );
        }
        else
        {
            std::cout << std::string(indents, ' ') << "Unimplemented statement print\n";
        }
        // if statement_container.contained_statement
    }
}