#include "./simpleexpressions.hpp"

namespace syntax_tree::simple_expressions
{
    SimpleExpressionContainer::SimpleExpressionContainer(VariantContainedExpression contained_expression)
    : _contained_expression(contained_expression)
    {
    }

    const SimpleExpressionContainer::VariantContainedExpression & SimpleExpressionContainer::contained_expression() const
    {
        return _contained_expression;
    }
}