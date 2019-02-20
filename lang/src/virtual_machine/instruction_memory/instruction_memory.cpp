#include "./instruction_memory.hpp"

namespace virtual_machine::instruction_memory
{
    InstructionMemory::InstructionMemory(std::vector<bytecode::instructions::InstructionContainer> instructions)
    : _instructions(instructions)
    {
    }

    const std::vector<bytecode::instructions::InstructionContainer> & InstructionMemory::instructions() const
    {
        return _instructions;
    }
}
