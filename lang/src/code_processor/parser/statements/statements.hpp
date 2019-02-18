#ifndef PARSER_STATEMENTS_HPP
#define PARSER_STATEMENTS_HPP

#include "../../../syntax_tree/statements/statements.hpp"
#include "../../tokens/tokens.hpp"
#include "../parse_error.hpp"
#include "../parse_result.hpp"

namespace parser::statements
{
    std::variant<ParseResult<syntax_tree::statements::StatementContainer>, ParseError>
    parse_statement_container(const std::vector<tokens::Token> & tokens, unsigned long start_idx);

    std::variant<ParseResult<syntax_tree::statements::CompoundExpressionStatement>, ParseError>
    parse_compound_expression_statement(const std::vector<tokens::Token> & tokens, unsigned long start_idx);
    

    // std::variant<ParseResult<syntax_tree::statements::ComplexExpressionStatement>, ParseError>
    // parse_complex_expression_statement(const std::vector<tokens::Token> & tokens, unsigned long start_idx);
}

#endif