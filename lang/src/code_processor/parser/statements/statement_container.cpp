#include "./statements.hpp"

namespace parser::statements
{
    std::variant<ParseResult<syntax_tree::statements::StatementContainer>, ParseError>
    parse_statement_container(const std::vector<tokens::Token> & tokens, unsigned long start_idx)
    {
        auto try_parse_compound_statement = parse_compound_expression_statement(tokens, start_idx);
        if (std::holds_alternative<ParseResult<syntax_tree::statements::CompoundExpressionStatement>>(try_parse_compound_statement))
        {
            auto parsed_compound_statements = std::get<ParseResult<syntax_tree::statements::CompoundExpressionStatement>>(try_parse_compound_statement);

            auto statement_container = syntax_tree::statements::StatementContainer(parsed_compound_statements.contained());

            return ParseResult<syntax_tree::statements::StatementContainer>(statement_container, parsed_compound_statements.consumed_count());
        }
        else
        {
            return std::get<ParseError>(try_parse_compound_statement);
            // return ParseError("Could not parse statement");
        }
    }
}
