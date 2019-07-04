#include "./terminal_expressions.hpp"

namespace parser::terminal_expressions
{
    std::variant<ParseResult<syntax_tree::terminal_expressions::StringLiteralExpression>, ParseError>
    parse_string_literal_expression(const std::vector<tokens::Token> & tokens, unsigned long start_idx)
    {
        if (tokens[start_idx].token_type() != tokens::TokenType::STRING_LITERAL)
        {
            return ParseError(
                "Expected " + tokens::tok_type_to_str(tokens::TokenType::STRING_LITERAL) +
                ", got " + tokens::tok_type_to_str(tokens[start_idx].token_type()),
                tokens[start_idx]
            );
        }

        std::string raw_text = tokens[start_idx].content_text();
        std::string without_quotation_marks = raw_text.substr(1, raw_text.length() - 2);

        // one for the string literal token
        unsigned long consumed_count = 1;

        return ParseResult<syntax_tree::terminal_expressions::StringLiteralExpression>(
            syntax_tree::terminal_expressions::StringLiteralExpression(without_quotation_marks),
            consumed_count
        );
        // tokens::TokenType expect_true_or_false_token = tokens[start_idx].token_type();

        // if (expect_true_or_false_token != tokens::TokenType::TRUE_KEYWORD &&
        //     expect_true_or_false_token != tokens::TokenType::FALSE_KEYWORD)
        // {
        //     return ParseError(
        //         "Expected " + tokens::tok_type_to_str(tokens::TokenType::TRUE_KEYWORD) +
        //         " or " = tokens::tok_type_to_str(tokens::TokenType::FALSE_KEYWORD) +
        //         ", got " + tokens::tok_type_to_str(expect_true_or_false_token),
        //         tokens[start_idx]
        //     );
        // }

        // bool value = expect_true_or_false_token == tokens::TokenType::TRUE_KEYWORD;

        // // for the true or false keyword token
        // unsigned long consumed_count = 1;

        // return ParseResult<syntax_tree::terminal_expressions::BoolLiteralExpression>(
        //     syntax_tree::terminal_expressions::BoolLiteralExpression(value),
        //     consumed_count
        // );

    }
}