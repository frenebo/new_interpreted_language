#include <iostream>
#include "./runner.hpp"
#include "./machine_state/machine_state.hpp"

namespace virtual_machine::runner
{
    std::optional<machine_state::MachineRuntimeError> run_bytecode(const std::vector<bytecode::instructions::InstructionContainer> & instructions)
    {
        auto machine_state = virtual_machine::machine_state::MachineState(instructions);

        bool done = false;
        while (!done)
        {
            std::optional<machine_state::MachineRuntimeError> possible_error =
                machine_state.execute_next_instruction();
            
            if (possible_error.has_value())
            {
                return possible_error;
            }
            
            done = machine_state.machine_done();
        }

        return std::optional<machine_state::MachineRuntimeError>();
    }
}