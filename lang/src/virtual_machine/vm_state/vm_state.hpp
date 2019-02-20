#ifndef VM_STATE_HPP
#define VM_STATE_HPP

#include "../data_stack/data_stack.hpp"
#include "../instruction_memory/instruction_memory.hpp"

namespace virtual_machine::vm_state
{
    class VirtualMachineState
    {
    public:
        VirtualMachineState(std::vector<bytecode::instructions::InstructionContainer> instructions);
    private:
        virtual_machine::data_stack::DataStack _data_stack;
        instruction_memory::InstructionMemory _instruction_memory;
    };
}

#endif
