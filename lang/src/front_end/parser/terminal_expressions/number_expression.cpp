#include "./terminal_expressions.hpp"

namespace parser::terminal_expressions
{
    std::variant<ParseResult<syntax_tree::terminal_expressions::NumberExpression>, ParseError>
    parse_number_expression(const std::vector<tokens::Token> & tokens, unsigned long start_idx)
    {
        tokens::Token next_token = tokens[start_idx];
        tokens::TokenType next_token_type = next_token.token_type();

        if (next_token_type != tokens::TokenType::INTEGER_NUM &&
            next_token_type != tokens::TokenType::FLOAT_NUM)
        {
            return ParseError(
                "Expected " + tokens::tok_type_to_str(tokens::TokenType::INTEGER_NUM) +
                " or " + tokens::tok_type_to_str(tokens::TokenType::FLOAT_NUM) +
                ", got " + tokens::tok_type_to_str(next_token_type),
                tokens[start_idx]
            );
        }

        // for the single identifier token
        unsigned long consumed_count = 1;
        std::string number_token_text = next_token.content_text();

        syntax_tree::terminal_expressions::NumberExpression::NumberType number_type =
            next_token_type == tokens::TokenType::FLOAT_NUM ?
                syntax_tree::terminal_expressions::NumberExpression::NumberType::FLOAT :
                syntax_tree::terminal_expressions::NumberExpression::NumberType::INT;

        auto number_exp = syntax_tree::terminal_expressions::NumberExpression(number_token_text, number_type);

        return ParseResult<syntax_tree::terminal_expressions::NumberExpression>(number_exp, consumed_count);
    }
}