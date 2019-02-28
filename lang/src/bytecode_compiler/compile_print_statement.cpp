#include "./bytecode_compiler.hpp"

namespace bytecode_compiler
{
    BytecodeCompiler::InstructionsOrErr BytecodeCompiler::compile_print_statement(const syntax_tree::statements::PrintStatement & print_statement)
    {
        auto try_parse_instructions = compile_compound_exp_evaluation(print_statement.exp_to_print());

        if (std::holds_alternative<BytecodeCompilerError>(try_parse_instructions))
        {
            return std::get<BytecodeCompilerError>(try_parse_instructions);
        }

        auto instructions = std::get<InstructionsVec>(try_parse_instructions);

        // print the resulting value
        instructions.push_back(bytecode::instructions::InstructionContainer(
            bytecode::instructions::StackPrint()
        ));

        return instructions;
    }
}