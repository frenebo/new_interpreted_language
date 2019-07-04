#include <iostream>
#include "./statements.hpp"
#include "../compound_expression/compound_expression.hpp"
#include "../statement_series/statement_series.hpp"

namespace syntax_tree_printer::statements
{
    void print_for_loop_statement(const syntax_tree::statements::ForLoopStatement & statement, unsigned int indents)
    {
        std::cout << std::string(indents, ' ') << "For Loop Statement:\n";

        std::cout << std::string(indents + 1, ' ') << "Setup Expression:\n";
        syntax_tree_printer::compound_expression::print_compound_expression(statement.setup_expression(), indents + 2);

        std::cout << std::string(indents + 1, ' ') << "Condition Expression:\n";
        syntax_tree_printer::compound_expression::print_compound_expression(statement.condition_expression(), indents + 2);

        std::cout << std::string(indents + 1, ' ') << "Increment Expression:\n";
        syntax_tree_printer::compound_expression::print_compound_expression(statement.increment_expression(), indents + 2);

        std::cout << std::string(indents + 1, ' ') << "Loop Body:\n";
        syntax_tree_printer::statement_series::print_statement_series(statement.loop_body(), indents + 2);
    }
}