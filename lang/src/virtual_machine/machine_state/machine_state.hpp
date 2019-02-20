#ifndef VM_MACHINE_STATE_HPP
#define VM_MACHINE_STATE_HPP

#include <optional>
#include <string>

#include "../data_stack/data_stack.hpp"
#include "../instruction_memory/instruction_memory.hpp"

namespace virtual_machine::machine_state
{
    class MachineRuntimeError
    {
    public:
        MachineRuntimeError(std::string message);
        const std::string & message() const;
    private:
        std::string _message;
    };
    
    class MachineState
    {
    public:
        MachineState(std::vector<bytecode::instructions::InstructionContainer> instructions);
        std::optional<MachineRuntimeError> execute_instruction();
        bool machine_done() const;
    private:
        bool _done;
        virtual_machine::data_stack::DataStack _data_stack;
        instruction_memory::InstructionMemory _instruction_memory;

        std::optional<MachineRuntimeError> execute_stack_add();
        std::optional<MachineRuntimeError> execute_stack_print();
        std::optional<MachineRuntimeError> execute_stack_int_push_const(bytecode::instructions::StackIntegerPushConst instruction);
        std::optional<MachineRuntimeError> execute_stack_subtract();
        // std::optional<MachineRuntimeError> execute_stack
        // std::optional<MachineRuntimeError> execute_stack
    };
}

#endif
