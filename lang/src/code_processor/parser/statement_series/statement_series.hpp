#ifndef PARSER_STATEMENT_SERIES_HPP
#define PARSER_STATEMENT_SERIES_HPP

#include <variant>
#include <vector>
#include "../../../syntax_tree/statement_series/statement_series.hpp"
#include "../../tokens/tokens.hpp"
#include "../parse_result.hpp"
#include "../parse_error.hpp"

namespace parser::statement_series
{
    std::variant<ParseResult<syntax_tree::statement_series::StatementSeries>, ParseError>
    parse_statement_series(const std::vector<tokens::Token> & tokens, unsigned long start_idx, tokens::TokenType stop_token);
}

#endif
