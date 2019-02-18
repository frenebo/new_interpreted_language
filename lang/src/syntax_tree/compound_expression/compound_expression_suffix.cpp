#include "./compound_expression.hpp"

namespace syntax_tree::compound_expression
{
    CompoundExpressionSuffix::CompoundExpressionSuffix(OperatorType op_type, PossiblyPrefixedTerminal terminal_exp)
    : _op_type(op_type),
    _terminal_exp(terminal_exp)
    {
    }

    OperatorType CompoundExpressionSuffix::op_type() const
    {
        return _op_type;
    }

    const PossiblyPrefixedTerminal &
    CompoundExpressionSuffix::terminal_exp() const
    {
        return _terminal_exp;
    }
}
