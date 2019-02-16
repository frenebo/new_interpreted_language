#include "./tokens.hpp"

namespace tokens
{
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