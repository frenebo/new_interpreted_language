#include "./statement_series.hpp"

namespace syntax_tree::statement_series
{
    StatementSeries::StatementSeries(std::vector<statements::StatementContainer> statements)
    : _statements(statements)
    {
    }

    const std::vector<statements::StatementContainer> & StatementSeries::statements() const
    {
        return _statements;
    }
}