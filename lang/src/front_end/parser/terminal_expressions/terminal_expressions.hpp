#ifndef PARSER_TERMINAL_EXPRESSIONS
#define PARSER_TERMINAL_EXPRESSIONS

#include <variant>
#include <vector>

#include "../parse_error.hpp"
#include "../parse_result.hpp"
#include "../../tokens/tokens.hpp"
#include "../../../syntax_tree/terminal_expressions/terminal_expressions.hpp"

namespace parser::terminal_expressions
{
    std::variant<ParseResult<syntax_tree::terminal_expressions::TerminalExpressionContainer>, ParseError>
    parse_terminal_expression_container(const std::vector<tokens::Token> & tokens, unsigned long start_idx);

    std::variant<ParseResult<syntax_tree::terminal_expressions::IdentifierExpression>, ParseError>
    parse_identifier_expression(const std::vector<tokens::Token> & tokens, unsigned long start_idx);

    std::variant<ParseResult<syntax_tree::terminal_expressions::NumberExpression>, ParseError>
    parse_number_expression(const std::vector<tokens::Token> & tokens, unsigned long start_idx);

    std::variant<ParseResult<syntax_tree::terminal_expressions::BoolLiteralExpression>, ParseError>
    parse_bool_literal_expression(const std::vector<tokens::Token> & tokens, unsigned long start_idx);
}

#endif
