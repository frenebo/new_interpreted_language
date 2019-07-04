#ifndef PARSE_ERROR_HPP
#define PARSE_ERROR_HPP

#include <string>

#include "../tokens/tokens.hpp"

namespace parser
{
    class ParseError
    {
    public:
        ParseError(std::string problem, tokens::Token error_token);
        const std::string & problem() const;
        const tokens::Token & error_token() const;
    private:
        std::string _problem;
        tokens::Token _error_token;
    };
}

#endif
