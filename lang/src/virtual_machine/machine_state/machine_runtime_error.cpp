#include "./machine_state.hpp"

namespace virtual_machine::machine_state
{
    MachineRuntimeError::MachineRuntimeError(std::string message)
    : _message(message)
    {
    }

    const std::string & MachineRuntimeError::message() const
    {
        return _message;
    }
}
