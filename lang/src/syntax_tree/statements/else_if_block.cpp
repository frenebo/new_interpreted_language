#include "./statements.hpp"

namespace syntax_tree::statements
{
    ElseIfBlock::ElseIfBlock(IfStatement if_statement)
    : _if_statement(if_statement)
    {
    }

    const syntax_tree::statements::IfStatement & ElseIfBlock::if_statement() const
    {
        return _if_statement.contained();
    }
}