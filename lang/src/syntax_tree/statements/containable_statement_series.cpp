#include "./statements.hpp"
#include "../statement_series/statement_series.hpp"

namespace syntax_tree::statements
{
    ContainableStatementSeries::ContainableStatementSeries(
        syntax_tree::statement_series::StatementSeries statement_series
    )
    : _statement_series(std::make_unique<syntax_tree::statement_series::StatementSeries>(statement_series))
    {
    }

    const syntax_tree::statement_series::StatementSeries & ContainableStatementSeries::statement_series() const
    {
        return *_statement_series;
    }

    ContainableStatementSeries::~ContainableStatementSeries()
    {
        _statement_series.reset(nullptr);
    }

    ContainableStatementSeries::ContainableStatementSeries(const ContainableStatementSeries & rhs)
    : _statement_series(std::make_unique<syntax_tree::statement_series::StatementSeries>(rhs.statement_series()))
    {
    }

    ContainableStatementSeries & ContainableStatementSeries::operator=(const ContainableStatementSeries & rhs)
    {
        _statement_series.reset(nullptr);
        _statement_series = std::make_unique<syntax_tree::statement_series::StatementSeries>(rhs.statement_series());

        return *this;
    }
}