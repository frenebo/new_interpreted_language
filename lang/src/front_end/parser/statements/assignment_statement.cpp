#include "./statements.hpp"
#include "../compound_expression/compound_expression.hpp"

namespace parser::statements
{
    std::variant<ParseResult<syntax_tree::statements::AssignmentStatement>, ParseError>
    parse_assignment_statement(const std::vector<tokens::Token> & tokens, unsigned long start_idx)
    {
        tokens::TokenType expect_identifier_tok = tokens[start_idx].token_type();

        if (expect_identifier_tok != tokens::TokenType::IDENTIFIER)
        {
            return ParseError(
                "Expected " + tokens::tok_type_to_str(tokens::TokenType::IDENTIFIER) +
                ", got " + tokens::tok_type_to_str(expect_identifier_tok)
            );
        }

        std::string identifier_string = tokens[start_idx].content_text();

        tokens::TokenType expect_equals_sign_tok = tokens[start_idx + 1].token_type();

        if (expect_equals_sign_tok != tokens::TokenType::EQUALS_SIGN)
        {
            return ParseError(
                "Expected " + tokens::tok_type_to_str(tokens::TokenType::EQUALS_SIGN) +
                ", got " = tokens::tok_type_to_str(expect_equals_sign_tok)
            );
        }

        // 2 for the identifier and equals sign
        unsigned long consumed_count = 2;

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
        tokens::TokenType expect_semicolon_tok = tokens[start_idx + consumed_count].token_type();
        if (expect_semicolon_tok != tokens::TokenType::SEMICOLON)
        {
            return ParseError(
                "Expected " + tokens::tok_type_to_str(tokens::TokenType::SEMICOLON) +
                ", got " + tokens::tok_type_to_str(expect_semicolon_tok)
            );
        }
        // for the semicolon
        consumed_count++;

        auto assignment_statement = syntax_tree::statements::AssignmentStatement(identifier_string, compound_expression);

        return ParseResult<syntax_tree::statements::AssignmentStatement>(assignment_statement, consumed_count);
    }
}