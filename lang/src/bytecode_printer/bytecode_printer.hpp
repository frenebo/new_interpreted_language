#ifndef BYTECODE_PRINTER_HPP
#define BYTECODE_PRINTER_HPP

#include <vector>
#include "../bytecode/instructions/instructions.hpp"

namespace bytecode_printer
{
    void print_instructions(const std::vector<bytecode::instructions::InstructionContainer> &);
    void print_instruction(const bytecode::instructions::InstructionContainer &);
}

#endif
