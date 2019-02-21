#include "./instructions.hpp"

namespace bytecode::instructions
{
    StackFloatPushConst::StackFloatPushConst(float value)
    : _value(value)
    {
    }

    float StackFloatPushConst::value() const
    {
        return _value;
    }
}