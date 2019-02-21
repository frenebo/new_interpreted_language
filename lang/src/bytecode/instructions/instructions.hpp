#ifndef BYTECODE_INSTRUCTIONS_HPP
#define BYTECODE_INSTRUCTIONS_HPP

#include <string>
#include <variant>
#include <optional>

namespace bytecode::instructions
{
    class StackAdd {};
    class StackSubtract {};
    class StackMultiply {};
    
    class StackIntegerPushConst {
    public:
        StackIntegerPushConst(int value);
        int value() const;
    private:
        int _value;
    };

    class StackFloatPushConst {
    public:
        StackFloatPushConst(float value);
        float value() const;
    private:
        float _value;
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

    class StackPop {};

    class InstructionContainer
    {
    public:
        typedef std::variant<
            StackAdd,
            StackSubtract,
            StackMultiply,
            StackIntegerPushConst,
            StackFloatPushConst,
            StackPrint,
            StackStoreToVariable,
            StackLoadFromVariable,
            StackPop
        > VariantInstruction;

        InstructionContainer(VariantInstruction contained_instruction);
        InstructionContainer(VariantInstruction, unsigned long line_label);

        const VariantInstruction & contained_instruction() const;
        std::optional<unsigned long> line_label() const;
        void set_line_label(unsigned long line_label);
    private:
        VariantInstruction _contained_instruction;
        std::optional<unsigned long> _line_label;
    };
}

#endif
