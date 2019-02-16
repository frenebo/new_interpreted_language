#include "./simpleexpressions.hpp"

namespace syntax_tree::simple_expressions
{
    IdentifierExpression::IdentifierExpression(std::string contained_text)
    : _contained_text(contained_text)
    {
    }

    const std::string & IdentifierExpression::contained_text() const
    {
        return _contained_text;
    }
}