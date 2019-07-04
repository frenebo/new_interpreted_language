#include "./statements.hpp"
#include "../compound_expression/compound_expression.hpp"

namespace parser::statements
{
    std::variant<ParseResult<syntax_tree::statements::PrintStatement>, ParseError>
    parse_print_statement(const std::vector<tokens::Token> & tokens, unsigned long start_idx)
    {
        // parse print keyword
        tokens::TokenType expect_print_keyword = tokens[start_idx].token_type();

        if (expect_print_keyword != tokens::TokenType::PRINT_KEYWORD)
        {
            return ParseError(
                "Expected " + tokens::tok_type_to_str(tokens::TokenType::PRINT_KEYWORD) +
                ", got " + tokens::tok_type_to_str(expect_print_keyword),
                tokens[start_idx]
            );
        }

        // one consumed for the print keyword
        unsigned long consumed_count = 1;

        // parse compound expression
        auto try_parse_compound_expression =
            parser::compound_expression::parse_compound_expression(tokens, start_idx + consumed_count, tokens::TokenType::SEMICOLON);

        if (std::holds_alternative<ParseError>(try_parse_compound_expression))
        {
            return std::get<ParseError>(try_parse_compound_expression);
        }

        auto parse_compound_expression_result =
            std::get<ParseResult<syntax_tree::compound_expression::CompoundExpression>>(try_parse_compound_expression);

        consumed_count += parse_compound_expression_result.consumed_count();
        auto compound_expression = parse_compound_expression_result.contained();

        // parse semicolon
        tokens::TokenType expect_semicolon_tok_type =
            tokens[start_idx + consumed_count].token_type();

        if (expect_semicolon_tok_type != tokens::TokenType::SEMICOLON)
        {
            return ParseError(
                "Expected " + tokens::tok_type_to_str(tokens::TokenType::SEMICOLON) +
                ", got " + tokens::tok_type_to_str(expect_print_keyword),
                tokens[start_idx + consumed_count]
            );
        }

        // for the semicolon
        consumed_count++;

        auto print_statement = syntax_tree::statements::PrintStatement(compound_expression);
        return ParseResult<syntax_tree::statements::PrintStatement>(print_statement, consumed_count);
    }
}