#ifndef PARSER_STATEMENT_SERIES_HPP
#define PARSER_STATEMENT_SERIES_HPP

#include <variant>
#include <vector>
#include "../../../syntaxtree/statementseries/statementseries.hpp"
#include "../../tokens/tokens.hpp"
#include "../parseresult.hpp"
#include "../parseerror.hpp"

namespace parser::statement_series
{
    std::variant<ParseResult<syntax_tree::statement_series::StatementSeries>, ParseError>
    parse_statement_series(const std::vector<tokens::Token> & tokens, unsigned long start_idx, tokens::TokenType stop_token);
}

#endif
