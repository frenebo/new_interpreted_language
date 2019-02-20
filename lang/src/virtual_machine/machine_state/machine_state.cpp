#include <iostream>
#include "./machine_state.hpp"


namespace virtual_machine::machine_state
{
    MachineState::MachineState(std::vector<bytecode::instructions::InstructionContainer> instructions)
    : _instruction_memory(instructions)
    {
        _done = false;
        _data_stack = data_stack::DataStack();
    }

    std::optional<MachineRuntimeError> MachineState::execute_instruction()
    {
        if (_instruction_memory.position() >= _instruction_memory.instructions().size())
        {
            _done = true;
            return std::optional<MachineRuntimeError>();
        }

        auto current_instruction_container = _instruction_memory.instructions()[_instruction_memory.position()];
        auto current_instruction = current_instruction_container.contained_instruction();

        // stack int add
        if (std::holds_alternative<bytecode::instructions::StackAdd>(current_instruction))
        {
            return execute_stack_add();
        }
        // stack int print
        else if (std::holds_alternative<bytecode::instructions::StackPrint>(current_instruction))
        {
            return execute_stack_print();
        }
        // stack int push
        else if (std::holds_alternative<bytecode::instructions::StackIntegerPushConst>(current_instruction))
        {
            return execute_stack_int_push_const(std::get<bytecode::instructions::StackIntegerPushConst>(current_instruction));
        }
        // stack int subtract
        else if (std::holds_alternative<bytecode::instructions::StackSubtract>(current_instruction))
        {
            return execute_stack_subtract();
        }
        else
        {
            return std::optional<MachineRuntimeError>("UNIMPLEMENTED INSTRUCTION");
        }
    }

    std::optional<MachineRuntimeError> MachineState::execute_stack_add()
    {
        auto rhs_container = _data_stack.pop().contained();
        auto lhs_container = _data_stack.pop().contained();

        if (std::holds_alternative<data_container::IntegerContainer>(rhs_container) &&
            std::holds_alternative<data_container::IntegerContainer>(lhs_container))
        {
            // auto instruction = std::get<bytecode::instructions::StackIntegerAdd>(current_instruction);
            int rhs_int = std::get<data_container::IntegerContainer>(rhs_container).value();
            int lhs_int = std::get<data_container::IntegerContainer>(lhs_container).value();
            auto new_int_container = data_container::IntegerContainer(rhs_int + lhs_int);
            auto value_container = data_container::DataContainer(new_int_container);
            _data_stack.push(value_container);
        
            _instruction_memory.set_position(_instruction_memory.position() + 1);
            
            return std::optional<MachineRuntimeError>();
        }
        else
        {
            return MachineRuntimeError("Incompatible or unsupported variables for addition");
        }
    }
    
    std::optional<MachineRuntimeError> MachineState::execute_stack_print()
    {
        auto stack_val = _data_stack.pop().contained();
        if (std::holds_alternative<data_container::IntegerContainer>(stack_val))
        {
            int int_val = std::get<data_container::IntegerContainer>(stack_val).value();
            std::cout << int_val << "\n";
        
            _instruction_memory.set_position(_instruction_memory.position() + 1);

            return std::optional<MachineRuntimeError>();
        }
        else
        {
            return MachineRuntimeError("Unsupported type for prints");
        }
        return std::optional<MachineRuntimeError>();
    }
    
    std::optional<MachineRuntimeError> MachineState::execute_stack_int_push_const(bytecode::instructions::StackIntegerPushConst instruction)
    {
        int int_to_push = instruction.value();
        auto int_container = data_container::IntegerContainer(int_to_push);
        auto value_container = data_container::DataContainer(int_container);
        _data_stack.push(value_container);
        
        _instruction_memory.set_position(_instruction_memory.position() + 1);
        
        return std::optional<MachineRuntimeError>();
    }
    
    std::optional<MachineRuntimeError> MachineState::execute_stack_subtract()
    {
        auto rhs_container = _data_stack.pop().contained();
        auto lhs_container = _data_stack.pop().contained();

        if (std::holds_alternative<data_container::IntegerContainer>(rhs_container) &&
            std::holds_alternative<data_container::IntegerContainer>(lhs_container))
        {
            int rhs_int = std::get<data_container::IntegerContainer>(rhs_container).value();
            int lhs_int = std::get<data_container::IntegerContainer>(lhs_container).value();

            int new_int_val = lhs_int - rhs_int;
            
            auto new_int_container = data_container::IntegerContainer(new_int_val);
            auto value_container = data_container::DataContainer(new_int_container);
            _data_stack.push(value_container);
        
            _instruction_memory.set_position(_instruction_memory.position() + 1);
            
            return std::optional<MachineRuntimeError>();
        }
        else
        {
            return MachineRuntimeError("Incompatible or unsupported values for subtraction");
        }
    }

    bool MachineState::machine_done() const
    {
        return _done;
    }
}
