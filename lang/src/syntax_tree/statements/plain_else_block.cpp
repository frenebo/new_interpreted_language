#include "./statements.hpp"

namespace syntax_tree::statements
{
    PlainElseBlock::PlainElseBlock(syntax_tree::statement_series::StatementSeries body_statement_series)
    : _body_statement_series(body_statement_series)
    {
    }

    const syntax_tree::statement_series::StatementSeries & PlainElseBlock::body_statement_series() const
    {
        return _body_statement_series.contained();
    }
}