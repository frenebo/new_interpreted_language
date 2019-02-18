#include "./terminal_expressions.hpp"

namespace parser::terminal_expressions
{
    std::variant<ParseResult<syntax_tree::terminal_expressions::TerminalExpressionContainer>, ParseError>
    parse_terminal_expression_container(const std::vector<tokens::Token> & tokens, unsigned long start_idx)
    {
        auto try_parse_identifier =
            parse_identifier_expression(tokens, start_idx);
        
        if (std::holds_alternative<ParseResult<syntax_tree::terminal_expressions::IdentifierExpression>>(try_parse_identifier))
        {
            auto parse_identifier_expression_result = std::get<ParseResult<syntax_tree::terminal_expressions::IdentifierExpression>>(try_parse_identifier);
            unsigned long consumed_count = parse_identifier_expression_result.consumed_count();
            auto identifier_expression = parse_identifier_expression_result.contained();
            
            auto terminal_exp_container = syntax_tree::terminal_expressions::TerminalExpressionContainer(identifier_expression);

            return ParseResult<syntax_tree::terminal_expressions::TerminalExpressionContainer>(terminal_exp_container, consumed_count);
        }
        else
        {
            return ParseError("Expected terminal expression");
        }
    }
}