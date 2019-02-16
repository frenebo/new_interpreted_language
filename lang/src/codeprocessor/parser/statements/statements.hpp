#ifndef PARSER_STATEMENTS_HPP
#define PARSER_STATEMENTS_HPP

#include "../../../syntaxtree/statements/statements.hpp"
#include "../../tokens/tokens.hpp"
#include "../parseerror.hpp"
#include "../parseresult.hpp"

namespace parser::statements
{
    std::variant<ParseResult<syntax_tree::statements::StatementContainer>, ParseError>
    parse_statement_container(const std::vector<tokens::Token> & tokens, unsigned long start_idx);

    std::variant<ParseResult<syntax_tree::statements::ComplexExpressionStatement>, ParseError>
    parse_complex_statement_expression(const std::vector<tokens::Token> & tokens, unsigned long start_idx);
}

#endif
