#include "./statementseries.hpp"

namespace syntax_tree::statement_series
{
    StatementSeries::StatementSeries(std::vector<statements::StatementContainer> statements)
    : _statements(statements)
    {
    }
}