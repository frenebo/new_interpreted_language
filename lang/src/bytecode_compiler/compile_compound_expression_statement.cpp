#include "./bytecode_compiler.hpp"

namespace bytecode_compiler
{
    BytecodeCompiler::InstructionsOrErr BytecodeCompiler::compile_compound_expression_statement(const syntax_tree::statements::CompoundExpressionStatement & compound_expression_statement)
    {
        auto try_compile_exp_instructions = compile_compound_exp_evaluation(compound_expression_statement.compound_exp());
        if (std::holds_alternative<BytecodeCompilerError>(try_compile_exp_instructions))
        {
            return std::get<BytecodeCompilerError>(try_compile_exp_instructions);
        }

        auto instructions = std::get<InstructionsVec>(try_compile_exp_instructions);

        // get rid of the resulting value
        instructions.push_back(bytecode::instructions::InstructionContainer(
            bytecode::instructions::StackPop()
        ));

        return instructions;
    }
}