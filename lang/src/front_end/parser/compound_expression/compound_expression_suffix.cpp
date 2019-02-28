#include "./compound_expression.hpp"

namespace parser::compound_expression
{
    std::variant<ParseResult<syntax_tree::compound_expression::CompoundExpressionSuffix>, ParseError>
    parse_compound_expression_suffix(const std::vector<tokens::Token> tokens, unsigned long start_idx)
    {
        // parse operator
        syntax_tree::compound_expression::OperatorType op_type;
        
        tokens::TokenType next_token_type = tokens[start_idx].token_type();
        if (next_token_type == tokens::TokenType::PLUS_SIGN)
        {
            op_type = syntax_tree::compound_expression::OperatorType::PLUS_OP;
        }
        else if (next_token_type == tokens::TokenType::MINUS_SIGN)
        {
            op_type = syntax_tree::compound_expression::OperatorType::MINUS_OP;
        }
        else if (next_token_type == tokens::TokenType::ASTERISK)
        {
            op_type = syntax_tree::compound_expression::OperatorType::MULT_OP;
        }
        else if (next_token_type == tokens::TokenType::FORWARD_SLASH)
        {
            op_type = syntax_tree::compound_expression::OperatorType::DIV_OP;
        }
        else if (next_token_type == tokens::TokenType::EQUALS_SIGN)
        {
            op_type = syntax_tree::compound_expression::OperatorType::ASSIGNMENT_OP;
        }
        else if (next_token_type == tokens::TokenType::PLUS_EQUALS)
        {
            op_type = syntax_tree::compound_expression::OperatorType::PLUS_EQUALS_ASSIGNMENT_OP;
        }
        else if (next_token_type == tokens::TokenType::MINUS_EQUALS)
        {
            op_type = syntax_tree::compound_expression::OperatorType::MINUS_EQUALS_ASSIGNMENT_OP;
        }
        else if (next_token_type == tokens::TokenType::LESS_THAN_OP)
        {
            op_type = syntax_tree::compound_expression::OperatorType::LESS_THAN_OP;
        }
        else if (next_token_type == tokens::TokenType::LESS_THAN_OR_EQUAL_OP)
        {
            op_type = syntax_tree::compound_expression::OperatorType::LESS_THAN_OR_EQUAL_OP;
        }
        else if (next_token_type == tokens::TokenType::MORE_THAN_OP)
        {
            op_type = syntax_tree::compound_expression::OperatorType::MORE_THAN_OP;
        }
        else if (next_token_type == tokens::TokenType::MORE_THAN_OR_EQUAL_OP)
        {
            op_type = syntax_tree::compound_expression::OperatorType::MORE_THAN_OR_EQUAL_OP;
        }
        else if (next_token_type == tokens::TokenType::DOUBLE_EQUALS)
        {
            op_type = syntax_tree::compound_expression::OperatorType::EQUALITY_COMPARISON_OP;
        }
        else
        {
            return ParseError("Unexpected token " + tokens::tok_type_to_str(next_token_type));
        }

        // for the operator
        unsigned long consumed_count = 1;
        
        // parse the terminal after the operator
        auto try_parse_possibly_prefixed_terminal_exp =
            parse_possibly_prefixed_terminal(tokens, start_idx + consumed_count);
        
        if (std::holds_alternative<ParseError>(try_parse_possibly_prefixed_terminal_exp))
        {
            return std::get<ParseError>(try_parse_possibly_prefixed_terminal_exp);
        }

        auto parse_possibly_prefixed_terminal_exp_result =
            std::get<ParseResult<syntax_tree::compound_expression::PossiblyPrefixedTerminal>>(try_parse_possibly_prefixed_terminal_exp);
        
        consumed_count += parse_possibly_prefixed_terminal_exp_result.consumed_count();
        auto possibly_prefixed_terminal_exp = parse_possibly_prefixed_terminal_exp_result.contained();

        auto compound_expression_suffix = syntax_tree::compound_expression::CompoundExpressionSuffix(op_type, possibly_prefixed_terminal_exp);

        return ParseResult<syntax_tree::compound_expression::CompoundExpressionSuffix>(compound_expression_suffix, consumed_count);
    }
}