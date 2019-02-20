#include "./statements.hpp"

namespace syntax_tree::statements
{
    PrintStatement::PrintStatement(syntax_tree::compound_expression::CompoundExpression exp_to_print)
    : _exp_to_print(exp_to_print)
    {
    }

    const syntax_tree::compound_expression::CompoundExpression &
    PrintStatement::exp_to_print() const
    {
        return _exp_to_print;
    }
}