#include "./instructions.hpp"

namespace instructions
{
    InstructionContainer::InstructionContainer(VariantInstruction contained)
    : _contained(contained)
    {
    }

    const InstructionContainer::VariantInstruction &
    InstructionContainer::contained() const
    {
        return _contained;
    }
}