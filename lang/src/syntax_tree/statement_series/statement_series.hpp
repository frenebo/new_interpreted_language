#ifndef STATEMENTSERIES_HPP
#define STATEMENTSERIES_HPP

#include <vector>
#include "../statements/statements.hpp"

namespace syntax_tree::statement_series
{
    class StatementSeries
    {
    public:
        StatementSeries(std::vector<statements::StatementContainer> statements);
        const std::vector<statements::StatementContainer> & statements() const;
    private:
        std::vector<statements::StatementContainer> _statements;
    };
}

#endif
