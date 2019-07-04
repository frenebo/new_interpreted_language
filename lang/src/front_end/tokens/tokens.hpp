#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <string>

namespace tokens
{
    enum TokenType {
        OPEN_PARENTHESIS,
        CLOSE_PARENTHESIS,
        OPEN_BRACE,
        CLOSE_BRACE,
        EQUALS_SIGN,
        PLUS_EQUALS,
        MINUS_EQUALS,
        PLUS_SIGN,
        MINUS_SIGN,
        ASTERISK,
        FORWARD_SLASH,
        SEMICOLON,
        INTEGER_NUM,
        FLOAT_NUM,
        IDENTIFIER,
        PRINT_KEYWORD,
        IF_KEYWORD,
        FOR_KEYWORD,
        TRUE_KEYWORD,
        FALSE_KEYWORD,
        WHITESPACE,
        LESS_THAN_OP,
        LESS_THAN_OR_EQUAL_OP,
        MORE_THAN_OP,
        MORE_THAN_OR_EQUAL_OP,
        DOUBLE_EQUALS,
        END_OF_INPUT,
    };

    std::string tok_type_to_str(TokenType);

    class Token
    {
    public:
        Token(TokenType token_type, unsigned long start_idx, std::string content_text);

        TokenType token_type() const;
        unsigned long start_idx() const;
        const std::string & content_text() const;
    private:
        TokenType _token_type;
        unsigned long _start_idx;
        std::string _content_text;
    };
}

#endif
