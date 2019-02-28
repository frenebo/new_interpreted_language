#include "./compound_exp_tree.hpp"

namespace bytecode_compiler::compound_exp_tree
{
    CompoundExpValueNode::CompoundExpValueNode(std::vector<bytecode::instructions::InstructionContainer> instructions)
    : _instructions(instructions)
    {
    }

    const std::vector<bytecode::instructions::InstructionContainer> &
    CompoundExpValueNode::instructions() const
    {
        return _instructions;
    }
}
