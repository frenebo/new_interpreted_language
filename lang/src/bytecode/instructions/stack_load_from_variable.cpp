#include "./instructions.hpp"

namespace bytecode::instructions
{
    StackLoadFromVariable::StackLoadFromVariable(const std::string & var_name)
    : _var_name(var_name)
    {
    }

    const std::string & StackLoadFromVariable::var_name() const
    {
        return _var_name;
    }
}