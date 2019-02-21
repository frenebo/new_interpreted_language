#include "./instruction_memory.hpp"

namespace virtual_machine::instruction_memory
{
    InstructionMemory::InstructionMemory()
    : _instructions(std::vector<bytecode::instructions::InstructionContainer>())
    {
        _position = 0;
    }
    
    InstructionMemory::InstructionMemory(std::vector<bytecode::instructions::InstructionContainer> instructions)
    : _instructions(instructions)
    {
        _position = 0;
    }

    void InstructionMemory::replace_instructions(std::vector<bytecode::instructions::InstructionContainer> instructions)
    {
        _position = 0;
        _instructions = instructions;
    }

    const std::vector<bytecode::instructions::InstructionContainer> & InstructionMemory::instructions() const
    {
        return _instructions;
    }

    unsigned long InstructionMemory::position() const
    {
        return _position;
    }

    void InstructionMemory::set_position(unsigned long new_pos)
    {
        _position = new_pos;
    }
}
