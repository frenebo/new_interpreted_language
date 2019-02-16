#include "./statements.hpp"

namespace parser::statements
{
    std::variant<ParseResult<syntax_tree::statements::StatementContainer>, ParseError>
    parse_statement_container(const std::vector<tokens::Token> & tokens, unsigned long start_idx)
    {
        auto try_parse_complex_statement = parse_complex_statement_expression(tokens, start_idx);
        if (std::holds_alternative<ParseResult<syntax_tree::statements::ComplexExpressionStatement>>(try_parse_complex_statement))
        {
            auto parsed_complex_statements = std::get<ParseResult<syntax_tree::statements::ComplexExpressionStatement>>(try_parse_complex_statement);

            auto statement_container = syntax_tree::statements::StatementContainer(parsed_complex_statements.contained());

            return ParseResult<syntax_tree::statements::StatementContainer>(statement_container, parsed_complex_statements.consumed_count());
        }
        else
        {
            return ParseError("Could not parse statement");
        }
    }
}
