#ifndef PARSE_ERROR_HPP
#define PARSE_ERROR_HPP

#include <string>

namespace parser
{
    class ParseError
    {
    public:
        ParseError(std::string message);
        const std::string & message() const;
    private:
        std::string _message;
    };
}

#endif
