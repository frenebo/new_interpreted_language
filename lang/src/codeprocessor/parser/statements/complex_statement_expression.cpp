#include "./statements.hpp"

namespace parser::statements
{

    std::variant<ParseResult<syntax_tree::statements::ComplexExpressionStatement>, ParseError>
    parse_complex_statement_expression(const std::vector<tokens::Token> & tokens, unsigned long start_idx)
    {
        
    }
}