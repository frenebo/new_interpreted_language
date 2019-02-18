#include "./statements.hpp"

namespace syntax_tree::statements
{
    CompoundExpressionStatement::CompoundExpressionStatement(syntax_tree::compound_expression::CompoundExpression compound_exp)
    : _compound_exp(compound_exp)
    {
    }

    const syntax_tree::compound_expression::CompoundExpression &
    CompoundExpressionStatement::compound_exp() const
    {
        return _compound_exp;
    }
}
