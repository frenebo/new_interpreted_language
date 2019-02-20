#include "./compound_expression.hpp"
#include "../terminal_expressions/terminal_expressions.hpp"

namespace parser::compound_expression
{
    std::variant<ParseResult<syntax_tree::compound_expression::PossiblyPrefixedTerminal>, ParseError>
    parse_possibly_prefixed_terminal(const std::vector<tokens::Token> tokens, unsigned long start_idx)
    {
        unsigned long consumed_count = 0;
        tokens::TokenType next_tok_type = tokens[start_idx + consumed_count].token_type();

        std::optional<syntax_tree::compound_expression::PrefixType> possible_prefix_type;
        // check for prefix
        if (next_tok_type == tokens::TokenType::MINUS_SIGN)
        {
            possible_prefix_type = syntax_tree::compound_expression::PrefixType::MINUS_PREFIX;
            // increment consumed count for the minus sign
            consumed_count++;
        }

        auto try_parse_terminal_exp_container =
            parser::terminal_expressions::parse_terminal_expression_container(tokens, start_idx + consumed_count);
        
        if (std::holds_alternative<ParseError>(try_parse_terminal_exp_container))
        {
            return std::get<ParseError>(try_parse_terminal_exp_container);
        }

        auto parse_terminal_exp_container_result =
            std::get<ParseResult<syntax_tree::terminal_expressions::TerminalExpressionContainer>>(try_parse_terminal_exp_container);

        auto terminal_exp_container = parse_terminal_exp_container_result.contained();
        consumed_count += parse_terminal_exp_container_result.consumed_count();

        auto possibly_prefixed_terminal = syntax_tree::compound_expression::PossiblyPrefixedTerminal(terminal_exp_container, possible_prefix_type);

        return ParseResult<syntax_tree::compound_expression::PossiblyPrefixedTerminal>(possibly_prefixed_terminal, consumed_count);
    }
}