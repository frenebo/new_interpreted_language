#include "./terminal_expressions.hpp"

namespace syntax_tree::terminal_expressions
{
    IdentifierExpression::IdentifierExpression(std::string identifier_string)
    : _identifier_string(identifier_string)
    {
    }

    const std::string & IdentifierExpression::identifier_string() const
    {
        return _identifier_string;
    }
}