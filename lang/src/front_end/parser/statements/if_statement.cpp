#include "./statements.hpp"
#include "../compound_expression/compound_expression.hpp"
#include "../statement_series/statement_series.hpp"

namespace parser::statements
{
    std::variant<ParseResult<syntax_tree::statements::IfStatement>, ParseError>
    parse_if_statement(const std::vector<tokens::Token> & tokens, unsigned long start_idx)
    {
        // parses statement of form: if (expression) { statement sequence }
        unsigned long consumed_count = 0;

        // if keyword
        tokens::TokenType expect_if_keyword_tok = tokens[start_idx + consumed_count].token_type();
        if (expect_if_keyword_tok != tokens::TokenType::IF_KEYWORD)
        {
            return ParseError(
                "Expected " + tokens::tok_type_to_str(tokens::TokenType::IF_KEYWORD) +
                ", got " + tokens::tok_type_to_str(expect_if_keyword_tok)
            );
        }
        // increment consumed count for the if keyword
        consumed_count++;

        // open parenthesis before condition expression
        tokens::TokenType expect_open_parenthesis_tok = tokens[start_idx + consumed_count].token_type();
        if (expect_open_parenthesis_tok != tokens::TokenType::OPEN_PARENTHESIS)
        {
            return ParseError(
                "Expected " + tokens::tok_type_to_str(tokens::TokenType::OPEN_PARENTHESIS) +
                ", got " + tokens::tok_type_to_str(expect_open_parenthesis_tok)
            );
        }
        // increment consumed count for the open parenthesis
        consumed_count++;

        // condition expression
        // the parser should stop parsing at the close parenthesis
        auto try_parse_condition_expression =
            parser::compound_expression::parse_compound_expression(tokens, start_idx + consumed_count, tokens::TokenType::CLOSE_PARENTHESIS);
        
        if (std::holds_alternative<ParseError>(try_parse_condition_expression))
        {
            return std::get<ParseError>(try_parse_condition_expression);
        }

        auto parse_condition_expression_result =
            std::get<ParseResult<syntax_tree::compound_expression::CompoundExpression>>(try_parse_condition_expression);
        auto condition_expression = parse_condition_expression_result.contained();
        
        // increase consumed count by the number of tokens in the condition expression
        consumed_count += parse_condition_expression_result.consumed_count();

        // close parenthesis after condition expression
        tokens::TokenType expect_close_parenthesis = tokens[start_idx + consumed_count].token_type();
        if (expect_close_parenthesis != tokens::TokenType::CLOSE_PARENTHESIS)
        {
            return ParseError(
                "Expected " + tokens::tok_type_to_str(tokens::TokenType::CLOSE_PARENTHESIS) +
                ", got " + tokens::tok_type_to_str(expect_close_parenthesis)
            );
        }
        // increment consumed count for the close parenthesis
        consumed_count++;

        // open brace before if body
        tokens::TokenType expect_open_brace = tokens[start_idx + consumed_count].token_type();
        if (expect_open_brace != tokens::TokenType::OPEN_BRACE)
        {
            return ParseError(
                "Expected " + tokens::tok_type_to_str(tokens::TokenType::OPEN_BRACE) +
                ", got " + tokens::tok_type_to_str(expect_open_brace)
            );
        }
        // increment consumed count for the open brace
        consumed_count++;

        // if body
        // the parser should stop looking for statements at the close brace
        auto try_parse_if_body =
            parser::statement_series::parse_statement_series(tokens, start_idx + consumed_count, tokens::TokenType::CLOSE_BRACE);
        
        if (std::holds_alternative<ParseError>(try_parse_if_body))
        {
            return std::get<ParseError>(try_parse_if_body);
        }

        auto parse_if_body_result =
            std::get<ParseResult<syntax_tree::statement_series::StatementSeries>>(try_parse_if_body);
        auto if_body_statement_series = parse_if_body_result.contained();
        // increase consumed count by the number of tokens in the if body
        consumed_count += parse_if_body_result.consumed_count();

        // close brace after if body
        tokens::TokenType expect_close_brace = tokens[start_idx + consumed_count].token_type();
        if (expect_close_brace != tokens::TokenType::CLOSE_BRACE)
        {
            return ParseError(
                "Expected " + tokens::tok_type_to_str(tokens::TokenType::CLOSE_BRACE) +
                ", got " + tokens::tok_type_to_str(expect_close_brace)
            );
        }
        // increment consumed count for the close brace
        consumed_count++;

        auto if_statement = syntax_tree::statements::IfStatement(condition_expression, if_body_statement_series);
        return ParseResult<syntax_tree::statements::IfStatement>(if_statement, consumed_count);
    }
}