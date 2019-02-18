#include <iostream>

#include "./statement_series.hpp"
#include "../statements/statements.hpp"

namespace syntax_tree_printer::statement_series
{
    void print_statement_series(const syntax_tree::statement_series::StatementSeries & statement_series, unsigned int indents)
    {
        std::cout << std::string(indents, ' ') + "Statement Series:\n";

        for (auto statement_container : statement_series.statements())
        {
            syntax_tree_printer::statements::print_statement_container(statement_container, indents + 1);
        }
    }
}