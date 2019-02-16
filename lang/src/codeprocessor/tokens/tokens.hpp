#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <string>

namespace tokens
{
    enum TokenType {
        EQUALS_SIGN,
        IDENTIFIER,
        WHITESPACE,
        END_OF_INPUT,
    };

    class Token
    {
        TokenType _token_type;
        std::string _content_text;
    public:
        Token(TokenType token_type, std::string content_text);

        TokenType token_type() const;
        const std::string & content_text() const;
    };
}

#endif
