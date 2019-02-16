#ifndef SIMPLE_EXPRESSIONS_HPP
#define SIMPLE_EXPRESSIONS_HPP

#include <variant>
#include <string>

namespace syntax_tree::simple_expressions
{
    class IdentifierExpression
    {
    public:
        IdentifierExpression(std::string contained_text);
        const std::string & contained_text() const;
    private:
        std::string _contained_text;
    };
    
    class SimpleExpressionContainer
    {
    public:
        typedef std::variant<IdentifierExpression> VariantContainedExpression;
        SimpleExpressionContainer(VariantContainedExpression contained_expression);
        const VariantContainedExpression & contained_expression() const;
    private:
        VariantContainedExpression _contained_expression;
    };
}

#endif
