#include "./instructions.hpp"

namespace bytecode::instructions
{
    InstructionContainer::InstructionContainer(
        unsigned long line_label,
        VariantInstruction contained_instruction)
    : _line_label(line_label),
    _contained_instruction(contained_instruction)
    {
    }

    const InstructionContainer::VariantInstruction &
    InstructionContainer::contained_instruction() const
    {
        return _contained_instruction;
    }

    unsigned long InstructionContainer::line_label() const
    {
        return _line_label;
    }
}