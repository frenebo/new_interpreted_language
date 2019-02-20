#include "./tokens.hpp"

namespace tokens
{
    std::string tok_type_to_str(TokenType tok_type)
    {
        switch (tok_type)
        {
        case EQUALS_SIGN:
            return "equals sign";
        case PLUS_SIGN:
            return "plus sign";
        case MINUS_SIGN:
            return "minus sign";
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
        case END_OF_INPUT:
            return "end of input";
        default:
            return "unimplemented token string";
        }
    }
    
    Token::Token(TokenType token_type, std::string content_text)
    : _token_type(token_type),
    _content_text(content_text)
    {
    }

    TokenType Token::token_type() const
    {
        return _token_type;
    }

    const std::string & Token::content_text() const
    {
        return _content_text;
    }
}