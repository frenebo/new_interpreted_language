#include "./terminal_expressions.hpp"

namespace syntax_tree::terminal_expressions
{
    NumberExpression::NumberExpression(std::string number_string, NumberType number_type)
    : _number_string(number_string),
    _number_type(number_type)
    {
    }

    const std::string & NumberExpression::number_string() const
    {
        return _number_string;
    }

    NumberExpression::NumberType NumberExpression::number_type() const
    {
        return _number_type;
    }
}