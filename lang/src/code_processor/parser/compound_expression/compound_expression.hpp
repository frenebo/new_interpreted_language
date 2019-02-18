#ifndef PARSER_COMPOUND_EXPRESSION
#define PARSER_COMPOUND_EXPRESSION

#include <variant>
#include <vector>

#include "../../../syntax_tree/compound_expression/compound_expression.hpp"
#include "../../tokens/tokens.hpp"
#include "../parse_result.hpp"
#include "../parse_error.hpp"

namespace parser::compound_expression
{
    std::variant<ParseResult<syntax_tree::compound_expression::CompoundExpression>, ParseError>
    parse_compound_expression(const std::vector<tokens::Token> tokens, unsigned long start_idx, tokens::TokenType stop_tok_type);

    std::variant<ParseResult<syntax_tree::compound_expression::PossiblyPrefixedTerminal>, ParseError>
    parse_possibly_prefixed_terminal(const std::vector<tokens::Token> tokens, unsigned long start_idx);

    std::variant<ParseResult<syntax_tree::compound_expression::CompoundExpressionSuffix>, ParseError>
    parse_compound_expression_suffix(const std::vector<tokens::Token> tokens, unsigned long start_idx);
}

#endif
