#include "./compound_expression.hpp"

namespace syntax_tree::compound_expression
{
    CompoundExpression::CompoundExpression(PossiblyPrefixedTerminal start_exp, std::vector<CompoundExpressionSuffix> suffixes)
    : _start_exp(start_exp),
    _suffixes(suffixes)
    {
    }

    const PossiblyPrefixedTerminal &
    CompoundExpression::start_exp() const
    {
        return _start_exp;
    }
    
    const std::vector<CompoundExpressionSuffix> &
    CompoundExpression::suffixes() const
    {
        return _suffixes;
    }
}