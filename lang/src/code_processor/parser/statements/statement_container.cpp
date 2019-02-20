#include "./statements.hpp"

namespace parser::statements
{
    std::variant<ParseResult<syntax_tree::statements::StatementContainer>, ParseError>
    parse_statement_container(const std::vector<tokens::Token> & tokens, unsigned long start_idx)
    {
        auto try_parse_print_statement = parse_print_statement(tokens, start_idx);
        if (std::holds_alternative<ParseResult<syntax_tree::statements::PrintStatement>>(try_parse_print_statement))
        {
            auto parsed_print_statement = std::get<ParseResult<syntax_tree::statements::PrintStatement>>(try_parse_print_statement);

            auto statement_container = syntax_tree::statements::StatementContainer(parsed_print_statement.contained());

            return ParseResult<syntax_tree::statements::StatementContainer>(statement_container, parsed_print_statement.consumed_count());
        }

        auto try_parse_compound_statement = parse_compound_expression_statement(tokens, start_idx);
        if (std::holds_alternative<ParseResult<syntax_tree::statements::CompoundExpressionStatement>>(try_parse_compound_statement))
        {
            auto parsed_compound_statement = std::get<ParseResult<syntax_tree::statements::CompoundExpressionStatement>>(try_parse_compound_statement);

            auto statement_container = syntax_tree::statements::StatementContainer(parsed_compound_statement.contained());

            return ParseResult<syntax_tree::statements::StatementContainer>(statement_container, parsed_compound_statement.consumed_count());
        }
        else
        {
            return std::get<ParseError>(try_parse_compound_statement);
        }
    }
}
