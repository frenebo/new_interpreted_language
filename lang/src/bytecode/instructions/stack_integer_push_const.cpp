#include "./instructions.hpp"

namespace bytecode::instructions
{
    StackIntegerPushConst::StackIntegerPushConst(int value)
    : _value(value)
    {
    }

    int StackIntegerPushConst::value() const
    {
        return _value;
    }
}