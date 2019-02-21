#ifndef VM_INSTRUCTION_MEMORY
#define VM_INSTRUCTION_MEMORY

#include <vector>

#include "../../bytecode/instructions/instructions.hpp"

namespace virtual_machine::instruction_memory
{
    class InstructionMemory
    {
    public:
        InstructionMemory();
        InstructionMemory(std::vector<bytecode::instructions::InstructionContainer> instructions);
        
        void replace_instructions(std::vector<bytecode::instructions::InstructionContainer> instructions);
        
        const std::vector<bytecode::instructions::InstructionContainer> & instructions() const;
        unsigned long position() const;
        void set_position(unsigned long new_pos);
    private:
        std::vector<bytecode::instructions::InstructionContainer> _instructions;
        unsigned long _position;
    };
}

#endif
