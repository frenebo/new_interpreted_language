#include <iostream>

#include "./machine_state.hpp"
#include "../data_container_utils/data_container_utils.hpp"

// #define MACHINE_STATE_DEBUG

#ifdef MACHINE_STATE_DEBUG
#include "../../bytecode_printer/bytecode_printer.hpp"
#endif

namespace virtual_machine::machine_state
{
    MachineState::MachineState()
    : _instruction_memory()
    {
        _done = true;
        _data_stack = data_stack::DataStack();
        _local_variable_memory = local_variable_memory::LocalVariableMemory();
    }

    MachineState::MachineState(std::vector<bytecode::instructions::InstructionContainer> instructions)
    : _instruction_memory(instructions)
    {
        _done = false;
        _data_stack = data_stack::DataStack();
        _local_variable_memory = local_variable_memory::LocalVariableMemory();
    }

    void MachineState::replace_instructions(std::vector<bytecode::instructions::InstructionContainer> instructions)
    {
        _done = false;
        _instruction_memory.replace_instructions(instructions);
    }

    std::optional<MachineRuntimeError> MachineState::execute_next_instruction()
    {

        if (_instruction_memory.position() >= _instruction_memory.instructions().size())
        {
            _done = true;
            return std::optional<MachineRuntimeError>();
        }

        auto current_instruction_container = _instruction_memory.instructions()[_instruction_memory.position()];
        auto current_instruction = current_instruction_container.contained_instruction();

    #ifdef MACHINE_STATE_DEBUG
        std::cout << "Executing instructions: ";
        bytecode_printer::print_instruction(current_instruction_container);
    #endif

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
            int int_to_push = std::get<bytecode::instructions::StackIntegerPushConst>(current_instruction).value();
            return execute_stack_int_push_const(int_to_push);
        }
        else if (std::holds_alternative<bytecode::instructions::StackFloatPushConst>(current_instruction))
        {
            float float_to_push = std::get<bytecode::instructions::StackFloatPushConst>(current_instruction).value();
            return execute_stack_float_push_const(float_to_push);
        }
        // stack int subtract
        else if (std::holds_alternative<bytecode::instructions::StackSubtract>(current_instruction))
        {
            return execute_stack_subtract();
        }
        else if (std::holds_alternative<bytecode::instructions::StackStoreToVariable>(current_instruction))
        {
            std::string var_name = std::get<bytecode::instructions::StackStoreToVariable>(current_instruction).var_name();

            return execute_stack_store_to_variable(var_name);
        }
        else if (std::holds_alternative<bytecode::instructions::StackMultiply>(current_instruction))
        {
            return execute_stack_multiply();
        }
        else if (std::holds_alternative<bytecode::instructions::StackDivide>(current_instruction))
        {
            return execute_stack_divide();
        }
        else if (std::holds_alternative<bytecode::instructions::StackLoadFromVariable>(current_instruction))
        {
            std::string var_name = std::get<bytecode::instructions::StackLoadFromVariable>(current_instruction).var_name();

            return execute_stack_load_from_variable(var_name);
        }
        else if (std::holds_alternative<bytecode::instructions::SkipNextInstructionIfStackValueTruthy>(current_instruction))
        {
            return execute_skip_next_instruction_if_stack_value_matches_bool(true);
        }
        else if (std::holds_alternative<bytecode::instructions::SkipNextInstructionIfStackValueFalsy>(current_instruction))
        {
            return execute_skip_next_instruction_if_stack_value_matches_bool(false);
        }
        else if (std::holds_alternative<bytecode::instructions::GotoRelativePosition>(current_instruction))
        {
            int relative_pos = std::get<bytecode::instructions::GotoRelativePosition>(current_instruction).move_distance();
            return execute_goto_relative_instruction_location(relative_pos);
        }
        else if (std::holds_alternative<bytecode::instructions::StackDuplicate>(current_instruction))
        {
            return execute_stack_duplicate();
        }
        else if (std::holds_alternative<bytecode::instructions::StackPop>(current_instruction))
        {
            return execute_stack_pop();
        }
        else if (std::holds_alternative<bytecode::instructions::StackCompareLessThan>(current_instruction))
        {
            return execute_stack_compare_less_than();
        }
        else if (std::holds_alternative<bytecode::instructions::StackCompareLessThanOrEqualTo>(current_instruction))
        {
            return execute_stack_compare_less_than_or_equal_to();
        }
        else if (std::holds_alternative<bytecode::instructions::StackApplyNot>(current_instruction))
        {
            return execute_stack_apply_not();
        }
        else
        {
            return MachineRuntimeError("UNIMPLEMENTED INSTRUCTION");
        }
    }

    std::optional<MachineRuntimeError> MachineState::execute_stack_compare_less_than()
    {
        auto try_get_rhs = _data_stack.pop();
        auto try_get_lhs = _data_stack.pop();
        
        if (!try_get_lhs.has_value()) return MachineRuntimeError("Stack error - ran out of values");
        if (!try_get_rhs.has_value()) return MachineRuntimeError("Stack error - ran out of values");
        
        auto compare_result = data_container_utils::less_than_op_containers(*try_get_lhs, *try_get_rhs);
        if (std::holds_alternative<data_container_utils::TypeError>(compare_result))
        {
            data_container_utils::TypeError type_err = std::get<data_container_utils::TypeError>(compare_result);
            return MachineRuntimeError("Type Error: " + type_err.problem());
        }

        data_container::DataContainer result_container = std::get<data_container::DataContainer>(compare_result);

        _data_stack.push(result_container);

        _instruction_memory.set_position(_instruction_memory.position() + 1);

        return std::optional<MachineRuntimeError>();
    }

    std::optional<MachineRuntimeError> MachineState::execute_stack_compare_less_than_or_equal_to()
    {
        auto try_get_rhs = _data_stack.pop();
        auto try_get_lhs = _data_stack.pop();
        
        if (!try_get_lhs.has_value()) return MachineRuntimeError("Stack error - ran out of values");
        if (!try_get_rhs.has_value()) return MachineRuntimeError("Stack error - ran out of values");
        
        auto compare_result = data_container_utils::less_than_or_equal_op_containers(*try_get_lhs, *try_get_rhs);
        if (std::holds_alternative<data_container_utils::TypeError>(compare_result))
        {
            data_container_utils::TypeError type_err = std::get<data_container_utils::TypeError>(compare_result);
            return MachineRuntimeError("Type Error: " + type_err.problem());
        }

        data_container::DataContainer result_container = std::get<data_container::DataContainer>(compare_result);

        _data_stack.push(result_container);

        _instruction_memory.set_position(_instruction_memory.position() + 1);

        return std::optional<MachineRuntimeError>();
    }

    std::optional<MachineRuntimeError> MachineState::execute_stack_apply_not()
    {
        auto try_get_stack_val = _data_stack.pop();

        if (!try_get_stack_val.has_value()) return MachineRuntimeError("Stack error - ran out of values");

        auto try_get_not_val = data_container_utils::get_value_not(*try_get_stack_val);
        if (std::holds_alternative<data_container_utils::TypeError>(try_get_not_val))
        {
            data_container_utils::TypeError type_err = std::get<data_container_utils::TypeError>(try_get_not_val);
        }

        data_container::DataContainer result_container = std::get<data_container::DataContainer>(try_get_not_val);

        _data_stack.push(result_container);

        _instruction_memory.set_position(_instruction_memory.position() + 1);

        return std::optional<MachineRuntimeError>();
    }

    std::optional<MachineRuntimeError> MachineState::execute_stack_duplicate()
    {
        auto try_get_stack_val = _data_stack.pop();
        if (!try_get_stack_val.has_value())
        {
            return MachineRuntimeError("Stack error - ran out of values");
        }

        _data_stack.push(*try_get_stack_val);
        _data_stack.push(*try_get_stack_val);

        _instruction_memory.set_position(_instruction_memory.position() + 1);

        return std::optional<MachineRuntimeError>();
    }

    std::optional<MachineRuntimeError> MachineState::execute_goto_relative_instruction_location(int relative_pos)
    {
        // @TODO give an error if the set position does not exist?
        _instruction_memory.set_position(_instruction_memory.position() + relative_pos);

        return std::optional<MachineRuntimeError>();
    }

    std::optional<MachineRuntimeError> MachineState::execute_skip_next_instruction_if_stack_value_matches_bool(bool match_bool)
    {
        auto stack_val = _data_stack.pop();
        if (!stack_val.has_value())
        {
            return MachineRuntimeError("Stack error - ran out of values");
        }

        auto try_convert_stack_val_to_bool = data_container_utils::convert_data_to_bool(*stack_val);
        if (std::holds_alternative<data_container_utils::TypeError>(try_convert_stack_val_to_bool))
        {
            auto conversion_error = std::get<data_container_utils::TypeError>(try_convert_stack_val_to_bool);
            return MachineRuntimeError(conversion_error.problem());
        }

        bool stack_val_to_bool = std::get<bool>(try_convert_stack_val_to_bool);

        if (stack_val_to_bool == match_bool)
        {
            // skip the next instruction
            _instruction_memory.set_position(_instruction_memory.position() + 2);
        }
        else
        {
            // continue to next instruction
            _instruction_memory.set_position(_instruction_memory.position() + 1);
        }

        return std::optional<MachineRuntimeError>();
    }

    std::optional<MachineRuntimeError> MachineState::execute_stack_load_from_variable(const std::string & var_name)
    {
        auto variable_value = _local_variable_memory.get_variable(var_name);

        if (!variable_value.has_value())
        {
            return MachineRuntimeError("No variable with name \"" + var_name + "\" defined");
        }

        _data_stack.push(*variable_value);

        _instruction_memory.set_position(_instruction_memory.position() + 1);

        return std::optional<MachineRuntimeError>();
    }

    std::optional<MachineRuntimeError> MachineState::execute_stack_multiply()
    {
        auto rhs_container_optional = _data_stack.pop();
        auto lhs_container_optional = _data_stack.pop();

        if (!(rhs_container_optional.has_value() && lhs_container_optional.has_value()))
        {
            return MachineRuntimeError("Stack error - ran out of values");
        }

        auto try_multiply = data_container_utils::multiply_data_containers(*lhs_container_optional, *rhs_container_optional);

        if (std::holds_alternative<data_container_utils::TypeError>(try_multiply))
        {
            auto type_error = std::get<data_container_utils::TypeError>(try_multiply);
            return MachineRuntimeError("Type Error: " + type_error.problem());
        }

        auto value_container = std::get<data_container::DataContainer>(try_multiply);

        _data_stack.push(value_container);

        _instruction_memory.set_position(_instruction_memory.position() + 1);

        return std::optional<MachineRuntimeError>();
    }

    std::optional<MachineRuntimeError> MachineState::execute_stack_divide()
    {
        auto rhs_container_optional = _data_stack.pop();
        auto lhs_container_optional = _data_stack.pop();

        if (!(rhs_container_optional.has_value() && lhs_container_optional.has_value()))
        {
            return MachineRuntimeError("Stack error - ran out of values");
        }

        auto try_divide = data_container_utils::divide_data_containers(*lhs_container_optional, *rhs_container_optional);

        if (std::holds_alternative<data_container_utils::TypeError>(try_divide))
        {
            auto type_error = std::get<data_container_utils::TypeError>(try_divide);
            return MachineRuntimeError("Type Error: " + type_error.problem());
        }

        auto value_container = std::get<data_container::DataContainer>(try_divide);

        _data_stack.push(value_container);

        _instruction_memory.set_position(_instruction_memory.position() + 1);

        return std::optional<MachineRuntimeError>();
    }

    std::optional<MachineRuntimeError> MachineState::execute_stack_store_to_variable(const std::string & var_name)
    {
        auto stack_val_container_optional = _data_stack.pop();

        if (!stack_val_container_optional.has_value())
        {
            return MachineRuntimeError("Stack error - no values left on stack");
        }

        auto val_container = *stack_val_container_optional;

        _local_variable_memory.set_variable(var_name, val_container);

        _instruction_memory.set_position(_instruction_memory.position() + 1);

        return std::optional<MachineRuntimeError>();
    }

    std::optional<MachineRuntimeError> MachineState::execute_stack_add()
    {
        auto rhs_container_optional = _data_stack.pop();
        auto lhs_container_optional = _data_stack.pop();

        if (!(rhs_container_optional.has_value() && lhs_container_optional.has_value()))
        {
            return MachineRuntimeError("Stack error - ran out of values");
        }

        auto try_add = data_container_utils::add_data_containers(*lhs_container_optional, *rhs_container_optional);
        if (std::holds_alternative<data_container_utils::TypeError>(try_add))
        {
            auto type_error = std::get<data_container_utils::TypeError>(try_add);
            return MachineRuntimeError("Type Error: " + type_error.problem());
        }

        auto value_container = std::get<data_container::DataContainer>(try_add);
        _data_stack.push(value_container);

        _instruction_memory.set_position(_instruction_memory.position() + 1);

        return std::optional<MachineRuntimeError>();
    }

    std::optional<MachineRuntimeError> MachineState::execute_stack_print()
    {
        auto stack_val_container_optional = _data_stack.pop();

        if (!stack_val_container_optional.has_value())
        {
            return MachineRuntimeError("Stack error - ran out of values");
        }

        auto try_convert_to_string = data_container_utils::convert_data_to_string(*stack_val_container_optional);
        if (std::holds_alternative<data_container_utils::TypeError>(try_convert_to_string))
        {
            auto type_error = std::get<data_container_utils::TypeError>(try_convert_to_string);
            return MachineRuntimeError("Type Error: " + type_error.problem());
        }

        std::string converted_to_string = std::get<std::string>(try_convert_to_string);

        std::cout << converted_to_string << "\n";

        _instruction_memory.set_position(_instruction_memory.position() + 1);

        return std::optional<MachineRuntimeError>();
    }

    std::optional<MachineRuntimeError> MachineState::execute_stack_float_push_const(float float_to_push)
    {
        auto float_container = data_container::FloatContainer(float_to_push);
        auto value_container = data_container::DataContainer(float_container);

        _data_stack.push(value_container);

        _instruction_memory.set_position(_instruction_memory.position() + 1);

        return std::optional<MachineRuntimeError>();
    }

    std::optional<MachineRuntimeError> MachineState::execute_stack_int_push_const(int int_to_push)
    {
        auto int_container = data_container::IntegerContainer(int_to_push);
        auto value_container = data_container::DataContainer(int_container);
        _data_stack.push(value_container);

        _instruction_memory.set_position(_instruction_memory.position() + 1);

        return std::optional<MachineRuntimeError>();
    }

    std::optional<MachineRuntimeError> MachineState::execute_stack_subtract()
    {
        auto rhs_container_optional = _data_stack.pop();
        auto lhs_container_optional = _data_stack.pop();

        if (!(rhs_container_optional.has_value() && lhs_container_optional.has_value()))
        {
            return MachineRuntimeError("Stack error - ran out of values");
        }

        auto try_subtract = data_container_utils::subtract_data_containers(*lhs_container_optional, *rhs_container_optional);

        if (std::holds_alternative<data_container_utils::TypeError>(try_subtract))
        {
            auto type_error = std::get<data_container_utils::TypeError>(try_subtract);
            return MachineRuntimeError("Type Error: " + type_error.problem());
        }

        auto value_container = std::get<data_container::DataContainer>(try_subtract);

        _data_stack.push(value_container);

        _instruction_memory.set_position(_instruction_memory.position() + 1);

        return std::optional<MachineRuntimeError>();
    }

    std::optional<MachineRuntimeError> MachineState::execute_stack_pop()
    {
        auto stack_val_container_optional = _data_stack.pop();

        if (!stack_val_container_optional.has_value())
        {
            return MachineRuntimeError("Stack error - ran out of values");
        }

        _instruction_memory.set_position(_instruction_memory.position() + 1);
        
        return std::optional<MachineRuntimeError>();
    }

    bool MachineState::machine_done() const
    {
        return _done;
    }
}
