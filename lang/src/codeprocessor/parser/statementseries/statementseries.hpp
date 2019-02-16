#ifndef PARSER_STATEMENT_SERIES_HPP
#define PARSER_STATEMENT_SERIES_HPP

#include <variant>
#include <vector>
#include "../../../syntaxtree/statementseries/statementseries.hpp"
#include "../../tokens/tokens.hpp"
#include "../parseerror.hpp"

namespace parser::statement_series
{
    std::variant<syntaxtree::statement_series::StatementSeries, ParseError>
    parse_statement_series(std::vector<tokens::Token> tokens, unsigned long start_idx, tokens::TokenType stop_token);
}

#endif
