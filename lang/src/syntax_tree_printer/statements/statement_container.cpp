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
        else
        {
            std::cout << std::string(indents, ' ') << "Unimplemented statement print\n";
        }
        // if statement_container.contained_statement
    }
}