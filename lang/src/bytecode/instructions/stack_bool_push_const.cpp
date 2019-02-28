#include "./instructions.hpp"

namespace bytecode::instructions
{
    StackBoolPushConst::StackBoolPushConst(bool value)
    : _value(value)
    {
    }

    bool StackBoolPushConst::value() const
    {
        return _value;
    }
}