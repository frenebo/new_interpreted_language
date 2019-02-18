#include "./compound_expression.hpp"

namespace parser::compound_expression
{
    std::variant<ParseResult<syntax_tree::compound_expression::CompoundExpression>, ParseError>
    parse_compound_expression(const std::vector<tokens::Token> tokens, unsigned long start_idx, tokens::TokenType stop_tok_type)
    {
        auto try_parse_start_exp =
            parse_possibly_prefixed_terminal(tokens, start_idx);
        
        if (std::holds_alternative<ParseError>(try_parse_start_exp))
        {
            return std::get<ParseError>(try_parse_start_exp);
        }

        auto parse_start_exp_result = std::get<ParseResult<syntax_tree::compound_expression::PossiblyPrefixedTerminal>>(try_parse_start_exp);
        unsigned long consumed_count = parse_start_exp_result.consumed_count();
        auto start_exp = parse_start_exp_result.contained();

        // keep parsing operator suffixes unless the next token is the stop_tok_type
        std::vector<syntax_tree::compound_expression::CompoundExpressionSuffix> suffixes;
        while (tokens[start_idx + consumed_count].token_type() != stop_tok_type)
        {
            auto try_parse_compound_exp_suffix =
                parse_compound_expression_suffix(tokens, start_idx + consumed_count);
            
            if (std::holds_alternative<ParseError>(try_parse_compound_exp_suffix))
            {
                return std::get<ParseError>(try_parse_compound_exp_suffix);
            }

            auto parse_compound_exp_suffix_result = std::get<ParseResult<syntax_tree::compound_expression::CompoundExpressionSuffix>>(try_parse_compound_exp_suffix);
            consumed_count += parse_compound_exp_suffix_result.consumed_count();
            auto compound_exp_suffix = parse_compound_exp_suffix_result.contained();

            suffixes.push_back(compound_exp_suffix);
        }

        auto compound_exp = syntax_tree::compound_expression::CompoundExpression(start_exp, suffixes);

        return ParseResult<syntax_tree::compound_expression::CompoundExpression>(compound_exp, consumed_count);
    }
}
