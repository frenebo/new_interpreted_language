#include "./parse_error.hpp"

namespace parser
{
    ParseError::ParseError(std::string problem, tokens::Token error_token):
    _problem(problem),
    _error_token(error_token)
    {
    }

    const std::string & ParseError::problem() const
    {
        return _problem;
    }

    const tokens::Token & ParseError::error_token() const
    {
        return _error_token;
    }
}