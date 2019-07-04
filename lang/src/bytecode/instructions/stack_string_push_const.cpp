#include "./instructions.hpp"

namespace bytecode::instructions
{
    StackStringPushConst::StackStringPushConst(std::string value)
    : _value(value)
    {
    }

    const std::string & StackStringPushConst::value() const
    {
        return _value;
    }
}