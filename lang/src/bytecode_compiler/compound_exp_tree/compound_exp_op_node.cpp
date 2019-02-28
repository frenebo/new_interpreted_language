#include "./compound_exp_tree.hpp"

namespace bytecode_compiler::compound_exp_tree
{
    CompoundExpOpNode::CompoundExpOpNode(CompoundExpNodeContainer lhs, syntax_tree::compound_expression::OperatorType op_type, CompoundExpNodeContainer rhs)
    : _lhs(std::make_unique<CompoundExpNodeContainer>(lhs)),
    _op_type(op_type),
    _rhs(std::make_unique<CompoundExpNodeContainer>(rhs))
    {
    }

    CompoundExpOpNode::~CompoundExpOpNode()
    {
        _lhs.reset(nullptr);
        _rhs.reset(nullptr);
    }

    CompoundExpOpNode::CompoundExpOpNode(const CompoundExpOpNode & other)
    : _lhs(std::make_unique<CompoundExpNodeContainer>(other.lhs())),
    _op_type(other.op_type()),
    _rhs(std::make_unique<CompoundExpNodeContainer>(other.rhs()))
    {
    }

    CompoundExpOpNode & CompoundExpOpNode::operator=(const CompoundExpOpNode & other)
    {
        _lhs.reset(nullptr);
        _lhs = std::make_unique<CompoundExpNodeContainer>(other.lhs());
        _op_type = other.op_type();
        _rhs.reset(nullptr);
        _rhs = std::make_unique<CompoundExpNodeContainer>(other.rhs());
        return *this;
    }

    const CompoundExpNodeContainer & CompoundExpOpNode::lhs() const
    {
        return *_lhs;
    }

    syntax_tree::compound_expression::OperatorType CompoundExpOpNode::op_type() const
    {
        return _op_type;
    }

    const CompoundExpNodeContainer & CompoundExpOpNode::rhs() const
    {
        return *_rhs;
    }
}
