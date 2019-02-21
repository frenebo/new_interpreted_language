#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <string>

namespace tokens
{
    enum TokenType {
        EQUALS_SIGN,
        PLUS_SIGN,
        MINUS_SIGN,
        ASTERISK,
        FORWARD_SLASH,
        SEMICOLON,
        INTEGER_NUM,
        FLOAT_NUM,
        IDENTIFIER,
        PRINT_KEYWORD,
        WHITESPACE,
        END_OF_INPUT,
    };

    std::string tok_type_to_str(TokenType);

    class Token
    {
    public:
        Token(TokenType token_type, std::string content_text);

        TokenType token_type() const;
        const std::string & content_text() const;
    private:
        TokenType _token_type;
        std::string _content_text;
    };
}

#endif
