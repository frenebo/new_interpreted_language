#include "./statements.hpp"

namespace syntax_tree::statements
{
    StatementContainer::StatementContainer(VariantContainedStatement contained_statement)
    : _contained_statement(contained_statement)
    {
    }

    const StatementContainer::VariantContainedStatement & StatementContainer::contained_statement() const
    {
        return _contained_statement;
    }
}