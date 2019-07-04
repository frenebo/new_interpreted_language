#include "./statements.hpp"
#include "../statement_series/statement_series.hpp"

namespace syntax_tree::statements
{
    IfStatement::IfStatement(
        syntax_tree::compound_expression::CompoundExpression if_condition,
        syntax_tree::statement_series::StatementSeries statement_series)
    : _if_condition(if_condition),
    _body_statement_series(ContainableStatementSeries(statement_series))
    {
    }

    const syntax_tree::compound_expression::CompoundExpression & IfStatement::if_condition() const
    {
        return _if_condition;
    }

    const syntax_tree::statement_series::StatementSeries & IfStatement::body_statement_series() const
    {
        return _body_statement_series.statement_series();
    }
}