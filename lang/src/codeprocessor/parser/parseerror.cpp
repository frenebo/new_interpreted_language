#include "./parseerror.hpp"

namespace parser
{
    ParseError::ParseError(std::string message):
    _message(message)
    {
    }

    const std::string & ParseError::message() const
    {
        return _message;
    }
}