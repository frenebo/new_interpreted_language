#include "./instruction_memory.hpp"

namespace virtual_machine::instruction_memory
{
    InstructionMemory::InstructionMemory(std::vector<instructions::InstructionContainer> instructions)
    : _instructions(instructions)
    {
    }
}
