#include "./tokens.hpp"

namespace tokens
{
    std::string tok_type_to_str(TokenType tok_type)
    {
        switch (tok_type)
        {
        case OPEN_PARENTHESIS:
            return "open parenthesis";
        case CLOSE_PARENTHESIS:
            return "close parenthesis";
        case OPEN_BRACE:
            return "open brace";
        case CLOSE_BRACE:
            return "close brace";
        case EQUALS_SIGN:
            return "equals sign";
        case PLUS_EQUALS:
            return "plus equals";
        case MINUS_EQUALS:
            return "minus equals";
        case PLUS_SIGN:
            return "plus sign";
        case MINUS_SIGN:
            return "minus sign";
        case ASTERISK:
            return "asterisk";
        case FORWARD_SLASH:
            return "forward slash";
        case SEMICOLON:
            return "semicolon";
        case INTEGER_NUM:
            return "integer";
        case FLOAT_NUM:
            return "float";
        case IDENTIFIER:
            return "identifier";
        case WHITESPACE:
            return "whitespace";
        case PRINT_KEYWORD:
            return "print keyword";
        case IF_KEYWORD:
            return "if keyword";
        case ELSE_KEYWORD:
            return "else keyword";
        case FOR_KEYWORD:
            return "for keyword";
        case END_OF_INPUT:
            return "end of input";
        case LESS_THAN_OP:
            return "< operator";
        case LESS_THAN_OR_EQUAL_OP:
            return "<= operator";
        case MORE_THAN_OP:
            return "> operator";
        case MORE_THAN_OR_EQUAL_OP:
            return ">= operator";
        case DOUBLE_EQUALS:
            return "== operator";
        case TRUE_KEYWORD:
            return "true keyword";
        case FALSE_KEYWORD:
            return "false keyword";
        case STRING_LITERAL:
            return "string literal";
        case PERCENT_SIGN:
            return "percent sign";
        case DOUBLE_VERTICAL_BAR:
            return "double vertical bar";
        case DOUBLE_AMPERSAND:
            return "double ampersand";
        case NOT_EQUALS:
            return "not equals";
        default:
            return "unimplemented token string";
        }
    }

    Token::Token(TokenType token_type, unsigned long start_idx, std::string content_text)
    : _token_type(token_type),
    _start_idx(start_idx),
    _content_text(content_text)
    {
    }

    TokenType Token::token_type() const
    {
        return _token_type;
    }

    unsigned long Token::start_idx() const
    {
        return _start_idx;
    }

    const std::string & Token::content_text() const
    {
        return _content_text;
    }
}