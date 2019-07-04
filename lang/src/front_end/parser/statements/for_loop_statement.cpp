#include "./statements.hpp"
#include "../compound_expression/compound_expression.hpp"
#include "../statement_series/statement_series.hpp"

namespace parser::statements
{
    std::variant<ParseResult<syntax_tree::statements::ForLoopStatement>, ParseError>
    parse_for_loop_statement(const std::vector<tokens::Token> & tokens, unsigned long start_idx)
    {
        unsigned long consumed_count = 0;

        // for keyword
        tokens::TokenType expect_for_keyword = tokens[start_idx + consumed_count].token_type();
        if (expect_for_keyword != tokens::TokenType::FOR_KEYWORD)
        {
            return ParseError(
                "Expected " + tokens::tok_type_to_str(tokens::TokenType::FOR_KEYWORD) +
                ", got " + tokens::tok_type_to_str(expect_for_keyword),
                tokens[start_idx + consumed_count]
            );
        }
        // for the "for" keyword
        consumed_count++;

        // open parenthesis before setup expression
        tokens::TokenType expect_open_paren_token = tokens[start_idx + consumed_count].token_type();
        if (expect_open_paren_token != tokens::TokenType::OPEN_PARENTHESIS)
        {
            return ParseError(
                "Expected " + tokens::tok_type_to_str(tokens::TokenType::OPEN_PARENTHESIS) +
                ", got " + tokens::tok_type_to_str(expect_open_paren_token),
                tokens[start_idx + consumed_count]
            );
        }
        // for the open parenthesis
        consumed_count++;

        // setup expression
        auto try_parse_setup_exp =
            parser::compound_expression::parse_compound_expression(tokens, start_idx + consumed_count, tokens::TokenType::SEMICOLON);
        if (std::holds_alternative<ParseError>(try_parse_setup_exp))
        {
            return std::get<ParseError>(try_parse_setup_exp);
        }
        auto parse_setup_exp_result =
            std::get<ParseResult<syntax_tree::compound_expression::CompoundExpression>>(try_parse_setup_exp);
        auto setup_exp = parse_setup_exp_result.contained();
        // increase consumed count by the number of tokens in the expression
        consumed_count += parse_setup_exp_result.consumed_count();

        // semicolon between the setup expression and the condition expression
        tokens::TokenType expect_semicolon_0 = tokens[start_idx + consumed_count].token_type();
        if (expect_semicolon_0 != tokens::TokenType::SEMICOLON)
        {
            return ParseError(
                "Expected " + tokens::tok_type_to_str(tokens::TokenType::SEMICOLON) +
                ", got " + tokens::tok_type_to_str(expect_semicolon_0),
                tokens[start_idx + consumed_count]
            );
        }
        // for the semicolon
        consumed_count++;

        // condition expression
        auto try_parse_condition_exp =
            parser::compound_expression::parse_compound_expression(tokens, start_idx + consumed_count, tokens::TokenType::SEMICOLON);
        if (std::holds_alternative<ParseError>(try_parse_condition_exp))
        {
            return std::get<ParseError>(try_parse_condition_exp);
        }
        auto parse_condition_exp_result =
            std::get<ParseResult<syntax_tree::compound_expression::CompoundExpression>>(try_parse_condition_exp);
        auto condition_exp = parse_condition_exp_result.contained();
        // increase consumed count by the number of tokens in the expression
        consumed_count += parse_condition_exp_result.consumed_count();

        // semicolon between the condition expression and the increment expression
        tokens::TokenType expect_semicolon_1 = tokens[start_idx + consumed_count].token_type();
        if (expect_semicolon_1 != tokens::TokenType::SEMICOLON)
        {
            return ParseError(
                "Expected " + tokens::tok_type_to_str(tokens::TokenType::SEMICOLON) +
                ", got " + tokens::tok_type_to_str(expect_semicolon_1),
                tokens[start_idx + consumed_count]
            );
        }
        // for the semicolon
        consumed_count++;

        // increment expression
        auto try_parse_increment_exp =
            parser::compound_expression::parse_compound_expression(tokens, start_idx + consumed_count, tokens::TokenType::CLOSE_PARENTHESIS);
        if (std::holds_alternative<ParseError>(try_parse_increment_exp))
        {
            ParseError exp_parse_err = std::get<ParseError>(try_parse_increment_exp);
            std::string problem = "Could not parse for loop increment expression: " + exp_parse_err.problem();
            return ParseError(problem, exp_parse_err.error_token());
        }
        auto parse_increment_exp_result =
            std::get<ParseResult<syntax_tree::compound_expression::CompoundExpression>>(try_parse_increment_exp);
        auto increment_exp = parse_increment_exp_result.contained();
        // increase consumed count by the number of tokens in the expression
        consumed_count += parse_increment_exp_result.consumed_count();

        // close parenthesis after the increment expression
        tokens::TokenType expect_close_parenthesis = tokens[start_idx + consumed_count].token_type();
        if (expect_close_parenthesis != tokens::TokenType::CLOSE_PARENTHESIS)
        {
            return ParseError(
                "Expected " + tokens::tok_type_to_str(tokens::TokenType::CLOSE_PARENTHESIS) +
                ", got " + tokens::tok_type_to_str(expect_close_parenthesis),
                tokens[start_idx + consumed_count]
            );
        }
        // increment the consumed count for the close parenthesis
        consumed_count++;

        // open brace before for body
        tokens::TokenType expect_open_brace = tokens[start_idx + consumed_count].token_type();
        if (expect_open_brace != tokens::TokenType::OPEN_BRACE)
        {
            return ParseError(
                "Expected " + tokens::tok_type_to_str(tokens::TokenType::OPEN_BRACE) +
                ", got " + tokens::tok_type_to_str(expect_open_brace),
                tokens[start_idx + consumed_count]
            );
        }
        // increment consumed count for the open brace
        consumed_count++;


        // if body
        // the parser should stop looking for statements at the close brace
        auto try_parse_for_loop_body =
            parser::statement_series::parse_statement_series(tokens, start_idx + consumed_count, tokens::TokenType::CLOSE_BRACE);

        if (std::holds_alternative<ParseError>(try_parse_for_loop_body))
        {
            return std::get<ParseError>(try_parse_for_loop_body);
        }

        auto parse_for_loop_body_result =
            std::get<ParseResult<syntax_tree::statement_series::StatementSeries>>(try_parse_for_loop_body);
        auto for_loop_body_statement_series = parse_for_loop_body_result.contained();
        // increase consumed count by the number of tokens in the if body
        consumed_count += parse_for_loop_body_result.consumed_count();

        // close brace after for body
        tokens::TokenType expect_close_brace = tokens[start_idx + consumed_count].token_type();
        if (expect_close_brace != tokens::TokenType::CLOSE_BRACE)
        {
            return ParseError(
                "Expected " + tokens::tok_type_to_str(tokens::TokenType::CLOSE_BRACE) +
                ", got " + tokens::tok_type_to_str(expect_close_brace),
                tokens[start_idx + consumed_count]
            );
        }
        // increment consumed count for the close brace
        consumed_count++;

        auto for_loop_statement = syntax_tree::statements::ForLoopStatement(
            setup_exp,
            condition_exp,
            increment_exp,
            for_loop_body_statement_series
        );

        return ParseResult<syntax_tree::statements::ForLoopStatement>(for_loop_statement, consumed_count);
    }
}