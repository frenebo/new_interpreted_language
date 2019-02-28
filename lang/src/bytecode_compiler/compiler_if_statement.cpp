#include "./bytecode_compiler.hpp"

namespace bytecode_compiler
{
    BytecodeCompiler::InstructionsOrErr BytecodeCompiler::compile_if_statement(const syntax_tree::statements::IfStatement & if_statement)
    {
        auto try_compile_condition_evaluate_instructions =
            compile_compound_exp_evaluation(if_statement.if_condition());
        if (std::holds_alternative<BytecodeCompilerError>(try_compile_condition_evaluate_instructions))
        {
            return std::get<BytecodeCompilerError>(try_compile_condition_evaluate_instructions);
        }
        auto condition_evaluate_instructions = std::get<InstructionsVec>(try_compile_condition_evaluate_instructions);

        auto try_compile_if_body_instructions =
            compile_statement_series(if_statement.body_statement_series());
        if (std::holds_alternative<BytecodeCompilerError>(try_compile_if_body_instructions))
        {
            return std::get<BytecodeCompilerError>(try_compile_if_body_instructions);
        }
        auto if_body_instructions = std::get<InstructionsVec>(try_compile_if_body_instructions);

        std::vector<bytecode::instructions::InstructionContainer> instructions;
        instructions.reserve(
            condition_evaluate_instructions.size() +
            2 +
            if_body_instructions.size()
        );
        // first, evaluate the condition
        instructions.insert(instructions.end(), condition_evaluate_instructions.begin(), condition_evaluate_instructions.end());
        // Skips the jump to the end of the if statement if the if condition is truthy
        instructions.push_back(bytecode::instructions::InstructionContainer(
            bytecode::instructions::SkipNextInstructionIfStackValueTruthy()
        ));
        // go to the instruction right after the end of the if body
        instructions.push_back(bytecode::instructions::InstructionContainer(
            bytecode::instructions::GotoRelativePosition(if_body_instructions.size() + 1)
        ));
        instructions.insert(instructions.end(), if_body_instructions.begin(), if_body_instructions.end());

        return instructions;
    }
}