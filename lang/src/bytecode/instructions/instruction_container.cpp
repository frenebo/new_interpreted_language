#include "./instructions.hpp"

namespace bytecode::instructions
{
    InstructionContainer::InstructionContainer(
        VariantInstruction contained_instruction)
    : _contained_instruction(contained_instruction),
    _line_label()
    {
    }

    InstructionContainer::InstructionContainer(
        VariantInstruction contained_instruction,
        unsigned long line_label)
    : _contained_instruction(contained_instruction),
    _line_label(line_label)
    {
    }

    const InstructionContainer::VariantInstruction &
    InstructionContainer::contained_instruction() const
    {
        return _contained_instruction;
    }

    std::optional<unsigned long> InstructionContainer::line_label() const
    {
        return _line_label;
    }
}