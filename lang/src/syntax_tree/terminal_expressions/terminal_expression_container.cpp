#include "./terminal_expressions.hpp"

namespace syntax_tree::terminal_expressions
{
    TerminalExpressionContainer::TerminalExpressionContainer(VariantTerminalExp contained_terminal_exp)
    : _contained_terminal_exp(contained_terminal_exp)
    {
    }

    const TerminalExpressionContainer::VariantTerminalExp &
    TerminalExpressionContainer::contained_terminal_exp() const
    {
        return _contained_terminal_exp;
    }
}