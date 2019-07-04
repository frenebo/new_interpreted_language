#ifndef SYNTAX_TREE_COMPOUND_EXPRESSION_HPP
#define SYNTAX_TREE_COMPOUND_EXPRESSION_HPP

#include <optional>
#include <vector>
#include "../terminal_expressions/terminal_expressions.hpp"

namespace syntax_tree::compound_expression
{
    enum PrefixType { MINUS_PREFIX };
    class PossiblyPrefixedTerminal
    {
    public:
        PossiblyPrefixedTerminal(syntax_tree::terminal_expressions::TerminalExpressionContainer, std::optional<PrefixType>);

        const syntax_tree::terminal_expressions::TerminalExpressionContainer & terminal_exp_container() const;
        std::optional<PrefixType> possible_prefix_type() const;
    private:
        syntax_tree::terminal_expressions::TerminalExpressionContainer _terminal_exp_container;
        std::optional<PrefixType> _possible_prefix_type;
    };

    enum OperatorType {
        PLUS_OP,
        MINUS_OP,
        MULT_OP,
        DIV_OP,
        MODULO_OP,
        ASSIGNMENT_OP,
        MINUS_EQUALS_ASSIGNMENT_OP,
        PLUS_EQUALS_ASSIGNMENT_OP,
        LESS_THAN_OP,
        LESS_THAN_OR_EQUAL_OP,
        MORE_THAN_OP,
        MORE_THAN_OR_EQUAL_OP,
        EQUALITY_COMPARISON_OP,
        AND_OP,
        OR_OP,
    };
    class CompoundExpressionSuffix
    {
    public:
        CompoundExpressionSuffix(OperatorType op_type, PossiblyPrefixedTerminal terminal_exp);
        OperatorType op_type() const;
        const PossiblyPrefixedTerminal & terminal_exp() const;

    private:
        OperatorType _op_type;
        PossiblyPrefixedTerminal _terminal_exp;
    };

    class CompoundExpression
    {
    public:
        CompoundExpression(PossiblyPrefixedTerminal start_exp, std::vector<CompoundExpressionSuffix> suffixes);

        const PossiblyPrefixedTerminal & start_exp() const;
        const std::vector<CompoundExpressionSuffix> & suffixes() const;
    private:
        PossiblyPrefixedTerminal _start_exp;
        std::vector<CompoundExpressionSuffix> _suffixes;
    };
}

#endif
