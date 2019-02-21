#include "./instructions.hpp"

namespace bytecode::instructions
{
    StackStoreToVariable::StackStoreToVariable(const std::string & var_name)
    : _var_name(var_name)
    {
    }

    const std::string & StackStoreToVariable::var_name() const
    {
        return _var_name;
    }
}
