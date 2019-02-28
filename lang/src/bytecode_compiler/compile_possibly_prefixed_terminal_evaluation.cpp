#include "./bytecode_compiler.hpp"

namespace bytecode_compiler
{
    BytecodeCompiler::InstructionsOrErr BytecodeCompiler::compile_possibly_prefixed_terminal_evaluation(const syntax_tree::compound_expression::PossiblyPrefixedTerminal & possibly_prefixed_terminal_expression)
    {
        InstructionsOrErr try_compile_terminal_instructions = compile_terminal_evaluation(possibly_prefixed_terminal_expression.terminal_exp_container());
        if (std::holds_alternative<BytecodeCompilerError>(try_compile_terminal_instructions))
        {
            return std::get<BytecodeCompilerError>(try_compile_terminal_instructions);
        }
        InstructionsVec instructions = std::get<InstructionsVec>(try_compile_terminal_instructions);

        auto possible_prefix_type = possibly_prefixed_terminal_expression.possible_prefix_type();
        if (possible_prefix_type.has_value())
        {
            if ((*possible_prefix_type) == syntax_tree::compound_expression::PrefixType::MINUS_PREFIX)
            {
                // multiply by negative one
                instructions.push_back(bytecode::instructions::InstructionContainer(
                    bytecode::instructions::StackIntegerPushConst(-1)
                ));

                instructions.push_back(bytecode::instructions::InstructionContainer(
                    bytecode::instructions::StackMultiply()
                ));
            }
            else
            {
                return BytecodeCompilerError("Compiler: unimplemented terminal value prefix\n");
            }
        }

        return instructions;
    }
}