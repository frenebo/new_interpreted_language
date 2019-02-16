#include "./lexer.hpp"

namespace lexer
{
    LexErrorMessage::LexErrorMessage(std::string reason)
    : _reason(reason)
    {
    }

    const std::string & LexErrorMessage::reason() const
    {
        return _reason;
    }
}