#include "./terminal_expressions.hpp"

namespace syntax_tree::terminal_expressions
{
    StringLiteralExpression::StringLiteralExpression(std::string string_text)
    : _string_text(string_text)
    {

    }

    const std::string & StringLiteralExpression::string_text() const
    {
        return _string_text;
    }
}