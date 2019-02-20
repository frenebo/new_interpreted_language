#ifndef VM_RUNNER_HPP
#define VM_RUNNER_HPP

#include "../bytecode/instructions/instructions.hpp"
#include "./machine_state/machine_state.hpp"

namespace virtual_machine::runner
{
    std::optional<machine_state::MachineRuntimeError> run_bytecode(const std::vector<bytecode::instructions::InstructionContainer> & instructions);
}

#endif
