#include "./statements.hpp"
#include "../compound_expression/compound_expression.hpp"

namespace parser::statements
{
    std::variant<ParseResult<syntax_tree::statements::CompoundExpressionStatement>, ParseError>
    parse_compound_expression_statement(const std::vector<tokens::Token> & tokens, unsigned long start_idx)
    {
        auto try_parse_compound_exp =
            parser::compound_expression::parse_compound_expression(tokens, start_idx, tokens::TokenType::SEMICOLON);

        if (std::holds_alternative<ParseError>(try_parse_compound_exp))
        {
            return std::get<ParseError>(try_parse_compound_exp);
        }

        auto parse_compound_exp_result =
            std::get<ParseResult<syntax_tree::compound_expression::CompoundExpression>>(try_parse_compound_exp);

        unsigned long consumed_count = parse_compound_exp_result.consumed_count();
        auto compound_exp = parse_compound_exp_result.contained();

        // is this redundant?
        tokens::TokenType expect_semicolon_type = tokens[start_idx + consumed_count].token_type();
        if (expect_semicolon_type != tokens::TokenType::SEMICOLON)
        {
            return ParseError(
                "Expected " + tokens::tok_type_to_str(tokens::TokenType::SEMICOLON) + ", got " + tokens::tok_type_to_str(expect_semicolon_type),
                tokens[start_idx + consumed_count]
            );
        }

        // for the semicolon
        consumed_count++;


        auto compound_exp_statement = syntax_tree::statements::CompoundExpressionStatement(compound_exp);

        return ParseResult<syntax_tree::statements::CompoundExpressionStatement>(compound_exp_statement, consumed_count);
    }
}