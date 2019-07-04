#include "./terminal_expressions.hpp"

namespace parser::terminal_expressions
{
    std::variant<ParseResult<syntax_tree::terminal_expressions::BoolLiteralExpression>, ParseError>
    parse_bool_literal_expression(const std::vector<tokens::Token> & tokens, unsigned long start_idx)
    {
        tokens::TokenType expect_true_or_false_token = tokens[start_idx].token_type();

        if (expect_true_or_false_token != tokens::TokenType::TRUE_KEYWORD &&
            expect_true_or_false_token != tokens::TokenType::FALSE_KEYWORD)
        {
            return ParseError(
                "Expected " + tokens::tok_type_to_str(tokens::TokenType::TRUE_KEYWORD) +
                " or " = tokens::tok_type_to_str(tokens::TokenType::FALSE_KEYWORD) +
                ", got " + tokens::tok_type_to_str(expect_true_or_false_token),
                tokens[start_idx]
            );
        }

        bool value = expect_true_or_false_token == tokens::TokenType::TRUE_KEYWORD;

        // for the true or false keyword token
        unsigned long consumed_count = 1;

        return ParseResult<syntax_tree::terminal_expressions::BoolLiteralExpression>(
            syntax_tree::terminal_expressions::BoolLiteralExpression(value),
            consumed_count
        );
    }
}
