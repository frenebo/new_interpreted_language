#include "./statementseries.hpp"
#include "../statements/statements.hpp"

namespace parser::statement_series
{
    std::variant<ParseResult<syntax_tree::statement_series::StatementSeries>, ParseError>
    parse_statement_series(const std::vector<tokens::Token> & tokens, unsigned long start_idx, tokens::TokenType stop_token)
    {
        std::vector<syntax_tree::statements::StatementContainer> statement_containers;

        unsigned long consumed_count = 0;

        while (tokens[start_idx + consumed_count].token_type() != stop_token)
        {
            unsigned long out_statement_container_consumed;
            auto statement_container_parse_result =
                parser::statements::parse_statement_container(tokens, start_idx + consumed_count);
            
            if (std::holds_alternative<ParseError>(statement_container_parse_result))
            {
                return std::get<ParseError>(statement_container_parse_result);
            }
            else
            {
                auto parse_result = std::get<ParseResult<syntax_tree::statements::StatementContainer>>(statement_container_parse_result);

                statement_containers.push_back(parse_result.contained());
                consumed_count += parse_result.consumed_count();
            }
        }
        
        return ParseResult(syntax_tree::statement_series::StatementSeries(statement_containers), consumed_count);
    }
}