#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <string>

namespace tokens
{
    enum TokenType {
        EQUALS_SIGN,
        PLUS_SIGN,
        SEMICOLON,
        INTEGER_NUM,
        FLOAT_NUM,
        IDENTIFIER,
        WHITESPACE,
        END_OF_INPUT,
    };

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
