#include "./statements.hpp"
#include "../statement_series/statement_series.hpp"

namespace syntax_tree::statements
{
    ForLoopStatement::ForLoopStatement(
        syntax_tree::compound_expression::CompoundExpression setup_expression,
        syntax_tree::compound_expression::CompoundExpression condition_expression,
        syntax_tree::compound_expression::CompoundExpression increment_expression,
        syntax_tree::statement_series::StatementSeries loop_body)
    : _setup_expression(setup_expression),
    _condition_expression(condition_expression),
    _increment_expression(increment_expression),
    _loop_body(std::make_unique<syntax_tree::statement_series::StatementSeries>(loop_body))
    {
    }
    const syntax_tree::compound_expression::CompoundExpression & ForLoopStatement::setup_expression() const
    {
        return _setup_expression;
    }
    
    const syntax_tree::compound_expression::CompoundExpression & ForLoopStatement::condition_expression() const
    {
        return _condition_expression;
    }
    
    const syntax_tree::compound_expression::CompoundExpression & ForLoopStatement::increment_expression() const
    {
        return _increment_expression;
    }

    const syntax_tree::statement_series::StatementSeries & ForLoopStatement::loop_body() const
    {
        return *_loop_body;
    }

    ForLoopStatement::~ForLoopStatement()
    {
        _loop_body.reset(nullptr);
    }

    ForLoopStatement::ForLoopStatement(const ForLoopStatement & rhs):
    _setup_expression(rhs.setup_expression()),
    _condition_expression(rhs.condition_expression()),
    _increment_expression(rhs.increment_expression()),
    _loop_body(std::make_unique<syntax_tree::statement_series::StatementSeries>(rhs.loop_body()))
    {
    }

    ForLoopStatement & ForLoopStatement::operator=(const ForLoopStatement & rhs)
    {
        _setup_expression = rhs.setup_expression();
        _condition_expression = rhs.condition_expression();
        _increment_expression = rhs.increment_expression();
        _loop_body.reset(nullptr);
        
        return *this;
    }
}
