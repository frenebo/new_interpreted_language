#include "./vm_state.hpp"

namespace virtual_machine::vm_state
{
    VirtualMachineState::VirtualMachineState(std::vector<bytecode::instructions::InstructionContainer> instructions)
    : _instruction_memory(instructions)
    {
        _data_stack = data_stack::DataStack();
    }
}
