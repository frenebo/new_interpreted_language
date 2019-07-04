#include "./terminal_expressions.hpp"

namespace parser::terminal_expressions
{
    std::variant<ParseResult<syntax_tree::terminal_expressions::IdentifierExpression>, ParseError>
    parse_identifier_expression(const std::vector<tokens::Token> & tokens, unsigned long start_idx)
    {
        tokens::Token next_token = tokens[start_idx];
        tokens::TokenType next_token_type = next_token.token_type();

        if (next_token_type != tokens::TokenType::IDENTIFIER)
        {
            return ParseError(
                "Expected " + tokens::tok_type_to_str(next_token_type) + ", got " +
                tokens::tok_type_to_str(next_token_type),
                tokens[start_idx]
            );
        }

        // for the single identifier token
        unsigned long consumed_count = 1;
        std::string identifier_token_text = next_token.content_text();

        auto identifier_exp = syntax_tree::terminal_expressions::IdentifierExpression(identifier_token_text);

        return ParseResult<syntax_tree::terminal_expressions::IdentifierExpression>(identifier_exp, consumed_count);
    }
}