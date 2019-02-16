#ifndef PARSE_ERROR_HPP
#define PARSE_ERROR_HPP

#include <string>

namespace parser
{
    class ParseError
    {
        std::string _message;
    public:
        ParseError(std::string message);
        const std::string & message() const;
    };
}

#endif
