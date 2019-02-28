#include "./terminal_expressions.hpp"

namespace syntax_tree::terminal_expressions
{
    BoolLiteralExpression::BoolLiteralExpression(bool value)
    : _value(value)
    {
    }

    bool BoolLiteralExpression::value() const
    {
        return _value;
    }
}