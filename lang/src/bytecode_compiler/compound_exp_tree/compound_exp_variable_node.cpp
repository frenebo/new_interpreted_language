#include "./compound_exp_tree.hpp"

namespace bytecode_compiler::compound_exp_tree
{
    CompoundExpVariableNode::CompoundExpVariableNode(std::string variable_name)
    : _variable_name(variable_name)
    {
    }

    const std::string & CompoundExpVariableNode::variable_name() const
    {
        return _variable_name;
    }
}