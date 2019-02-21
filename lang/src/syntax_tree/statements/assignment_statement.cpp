#include "./statements.hpp"

namespace syntax_tree::statements
{
    AssignmentStatement::AssignmentStatement(std::string var_name, syntax_tree::compound_expression::CompoundExpression assigned_exp)
    : _var_name(var_name),
    _assigned_exp(assigned_exp)
    {
    }

    const std::string & AssignmentStatement::var_name() const
    {
        return _var_name;
    }

    const syntax_tree::compound_expression::CompoundExpression & AssignmentStatement::assigned_exp() const
    {
        return _assigned_exp;
    }
}