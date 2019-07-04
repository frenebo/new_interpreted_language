#include <iostream>
#include "./statements.hpp"
#include "../compound_expression/compound_expression.hpp"
#include "../statement_series/statement_series.hpp"

namespace syntax_tree_printer::statements
{
    void print_if_statement(const syntax_tree::statements::IfStatement & statement, unsigned int indents)
    {
        std::cout << std::string(indents, ' ') << "If Statement:\n";

        std::cout << std::string(indents + 1, ' ') << "Condition:\n";
        syntax_tree_printer::compound_expression::print_compound_expression(statement.if_condition(), indents + 2);

        std::cout << std::string(indents + 1, ' ') << "If Body:\n";
        syntax_tree_printer::statement_series::print_statement_series(statement.body_statement_series(), indents + 2);

        if (statement.else_block().has_value())
        {
            const auto & else_val = *statement.else_block();
            std::cout << std::string(indents + 1, ' ') << "Else:";
            if (std::holds_alternative<syntax_tree::statements::ElseIfBlock>(else_val))
            {
                print_if_statement(std::get<syntax_tree::statements::ElseIfBlock>(else_val).if_statement(), indents + 1);
            }
            else if (std::holds_alternative<syntax_tree::statements::PlainElseBlock>(else_val))
            {
                syntax_tree_printer::statement_series::print_statement_series(
                    std::get<syntax_tree::statements::PlainElseBlock>(else_val).body_statement_series(),
                    indents + 1
                );
            }
            else
            {
                std::cout << "unimplemented else block type\n";
            }
        }
    }
}