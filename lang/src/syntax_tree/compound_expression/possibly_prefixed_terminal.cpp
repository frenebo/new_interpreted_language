#include "./compound_expression.hpp"

namespace syntax_tree::compound_expression
{
    PossiblyPrefixedTerminal::PossiblyPrefixedTerminal(
        syntax_tree::terminal_expressions::TerminalExpressionContainer terminal_exp_container,
        std::optional<PrefixType> possible_prefix_type)
    : _terminal_exp_container(terminal_exp_container),
    _possible_prefix_type(possible_prefix_type)
    {
    }

    const syntax_tree::terminal_expressions::TerminalExpressionContainer &
    PossiblyPrefixedTerminal::terminal_exp_container() const
    {
        return _terminal_exp_container;
    }

    std::optional<PrefixType> PossiblyPrefixedTerminal::possible_prefix_type() const
    {
        return _possible_prefix_type;
    }
}
