#include "./statementseries.hpp"

namespace parser::statement_series
{
    std::variant<syntaxtree::statement_series::StatementSeries, ParseError>
    parse_statement_series(std::vector<tokens::Token> tokens, unsigned long start_idx, tokens::TokenType stop_token)
    {
        return syntaxtree::statement_series::StatementSeries();
    }
}