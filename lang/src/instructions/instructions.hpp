#ifndef BYTECODE_HPP
#define BYTECODE_HPP

#include <variant>

namespace instructions
{
    class StackIntAdd {};
    class StackIntSubtract {};
    class StackFloatAdd {};
    class StackFloatSubtract{};

    class InstructionContainer
    {
    public:
        typedef std::variant<
            StackIntAdd,
            StackIntSubtract,
            StackFloatAdd,
            StackFloatSubtract
        > VariantInstruction;

        InstructionContainer(VariantInstruction contained);
        const VariantInstruction & contained() const;
    private:
        VariantInstruction _contained;
    };
}

#endif
