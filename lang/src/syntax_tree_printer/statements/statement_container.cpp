#include <iostream>
#include "./statements.hpp"

namespace syntax_tree_printer::statements
{
    void print_compound_expression_statement(const syntax_tree::statements::CompoundExpressionStatement & compound_exp_statement, unsigned int indents)
    {
        std::cout << std::string(indents, ' ') << "Compound Expression Statement:\n";

        syntax_tree_printer::compound_expression::print_compound_expression(compound_exp_statement.compound_exp());
    }
    
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
        // if statement_container.contained_statement
    }
}