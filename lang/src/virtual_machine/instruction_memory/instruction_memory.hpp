#ifndef VM_INSTRUCTION_MEMORY
#define VM_INSTRUCTION_MEMORY

#include <vector>

#include "../../bytecode/instructions/instructions.hpp"

namespace virtual_machine::instruction_memory
{
    class InstructionMemory
    {
    public:
        InstructionMemory(std::vector<bytecode::instructions::InstructionContainer> instructions);
        const std::vector<bytecode::instructions::InstructionContainer> & instructions() const;
    private:
        std::vector<bytecode::instructions::InstructionContainer> _instructions;
        unsigned long _position;
    };
}

#endif
