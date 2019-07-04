#ifndef BYTECODE_INSTRUCTIONS_HPP
#define BYTECODE_INSTRUCTIONS_HPP

#include <string>
#include <variant>
#include <optional>

namespace bytecode::instructions
{
    class StackAndOperation {};
    class StackOrOperation {};
    class StackAdd {};
    class StackSubtract {};
    class StackMultiply {};
    class StackDivide {};

    class StackCompareLessThan {};
    class StackCompareLessThanOrEqualTo {};
    class StackApplyNot {};
    class StackModuloOperation {};

    class StackBoolPushConst
    {
    public:
        StackBoolPushConst(bool value);
        bool value() const;
    private:
        bool _value;
    };

    class StackIntegerPushConst
    {
    public:
        StackIntegerPushConst(int value);
        int value() const;
    private:
        int _value;
    };

    class StackFloatPushConst
    {
    public:
        StackFloatPushConst(float value);
        float value() const;
    private:
        float _value;
    };

    class StackStringPushConst
    {
    public:
        StackStringPushConst(std::string value);
        const std::string & value() const;
    private:
        std::string _value;
    };

    class StackPrint {};

    class StackStoreToVariable
    {
    public:
        StackStoreToVariable(const std::string & var_name);
        const std::string & var_name() const;
    private:
        std::string _var_name;
    };

    class StackLoadFromVariable
    {
    public:
        StackLoadFromVariable(const std::string & var_name);
        const std::string & var_name() const;
    private:
        std::string _var_name;
    };

    class StackPop {};
    class StackDuplicate {};

    class SkipNextInstructionIfStackValueTruthy {};
    class SkipNextInstructionIfStackValueFalsy {};

    class GotoRelativePosition
    {
    public:
        // move_distance can be negative to move backwards, positive to move forwards.
        GotoRelativePosition(int move_distance);
        int move_distance() const;
    private:
        int _move_distance;
    };

    class InstructionContainer
    {
    public:
        typedef std::variant<
            StackAndOperation,
            StackOrOperation,
            StackAdd,
            StackSubtract,
            StackMultiply,
            StackDivide,
            StackCompareLessThan,
            StackCompareLessThanOrEqualTo,
            StackApplyNot,
            StackModuloOperation,
            StackIntegerPushConst,
            StackFloatPushConst,
            StackBoolPushConst,
            StackStringPushConst,
            StackPrint,
            StackStoreToVariable,
            StackLoadFromVariable,
            StackPop,
            StackDuplicate,
            GotoRelativePosition,
            SkipNextInstructionIfStackValueFalsy,
            SkipNextInstructionIfStackValueTruthy
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
