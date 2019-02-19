#ifndef VM_INSTRUCTION_MEMORY
#define VM_INSTRUCTION_MEMORY

#include <vector>

#include "../../instructions/instructions.hpp"

namespace virtual_machine::instruction_memory
{
    class InstructionMemory
    {
    public:
        InstructionMemory(std::vector<instructions::InstructionContainer> instructions);
        
    private:
        std::vector<instructions::InstructionContainer> _instructions;
    };
}

#endif
