#include "./terminal_expressions.hpp"

namespace parser::terminal_expressions
{
    std::variant<ParseResult<syntax_tree::terminal_expressions::TerminalExpressionContainer>, ParseError>
    parse_terminal_expression_container(const std::vector<tokens::Token> & tokens, unsigned long start_idx)
    {
        tokens::TokenType next_tok_type = tokens[start_idx].token_type();

        if (next_tok_type == tokens::TokenType::IDENTIFIER)
        {
            auto try_parse_identifier =
                parse_identifier_expression(tokens, start_idx);
            
            if (std::holds_alternative<ParseError>(try_parse_identifier))
            {
                return std::get<ParseError>(try_parse_identifier);
            }

            auto parse_identifier_expression_result = std::get<ParseResult<syntax_tree::terminal_expressions::IdentifierExpression>>(try_parse_identifier);
            unsigned long consumed_count = parse_identifier_expression_result.consumed_count();
            auto identifier_expression = parse_identifier_expression_result.contained();
            
            auto terminal_exp_container = syntax_tree::terminal_expressions::TerminalExpressionContainer(identifier_expression);

            return ParseResult<syntax_tree::terminal_expressions::TerminalExpressionContainer>(terminal_exp_container, consumed_count);
        }
        else if (next_tok_type == tokens::TokenType::FLOAT_NUM ||
            next_tok_type == tokens::TokenType::INTEGER_NUM)
        {
            auto try_parse_identifier =
                parse_number_expression(tokens, start_idx);
            
            if (std::holds_alternative<ParseError>(try_parse_identifier))
            {
                return std::get<ParseError>(try_parse_identifier);
            }

            auto parse_number_expression_result = std::get<ParseResult<syntax_tree::terminal_expressions::NumberExpression>>(try_parse_identifier);
            unsigned long consumed_count = parse_number_expression_result.consumed_count();
            auto number_expression = parse_number_expression_result.contained();

            auto terminal_exp_container = syntax_tree::terminal_expressions::TerminalExpressionContainer(number_expression);

            return ParseResult<syntax_tree::terminal_expressions::TerminalExpressionContainer>(terminal_exp_container, consumed_count);
        }
        else
        {
            return ParseError("Expected expression token, got " + tokens::tok_type_to_str(next_tok_type));
        }
    }
}
