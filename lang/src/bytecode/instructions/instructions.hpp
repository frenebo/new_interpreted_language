#ifndef BYTECODE_INSTRUCTIONS_HPP
#define BYTECODE_INSTRUCTIONS_HPP

#include <variant>

namespace bytecode::instructions
{
    // class StackInteger
    class StackAdd {};
    class StackSubtract {};
    
    class StackIntegerPushConst {
    public:
        StackIntegerPushConst(int value);
        int value() const;
    private:
        int _value;
    };

    class StackPrint {};
    
    class InstructionContainer
    {
    public:
        typedef std::variant<
            StackAdd,
            StackSubtract,
            StackIntegerPushConst,
            StackPrint
        > VariantInstruction;

        InstructionContainer(unsigned long line_label, VariantInstruction contained_instruction);

        const VariantInstruction & contained_instruction() const;
        unsigned long line_label() const;
    private:
        VariantInstruction _contained_instruction;
        unsigned long _line_label;
    };
}

#endif
