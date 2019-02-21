#ifndef BYTECODE_INSTRUCTIONS_HPP
#define BYTECODE_INSTRUCTIONS_HPP

#include <string>
#include <variant>

namespace bytecode::instructions
{
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

    class StackStoreToVariable {
    public:
        StackStoreToVariable(const std::string & var_name);
        const std::string & var_name() const;
    private:
        std::string _var_name;
    };

    class StackLoadFromVariable {
    public:
        StackLoadFromVariable(const std::string & var_name);
        const std::string & var_name() const;
    private:
        std::string _var_name;
    };

    class InstructionContainer
    {
    public:
        typedef std::variant<
            StackAdd,
            StackSubtract,
            StackIntegerPushConst,
            StackPrint,
            StackStoreToVariable,
            StackLoadFromVariable
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
