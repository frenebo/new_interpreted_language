#include "./bytecode_compiler.hpp"

namespace bytecode_compiler
{

    BytecodeCompiler::InstructionsOrErr BytecodeCompiler::compile_statement_series(const syntax_tree::statement_series::StatementSeries & statement_series)
    {
        std::vector<bytecode::instructions::InstructionContainer> instructions;

        for (const syntax_tree::statements::StatementContainer & statement_container : statement_series.statements())
        {
            auto try_compiler_statement_instructions = compile_statement_container(statement_container);
            if (std::holds_alternative<BytecodeCompilerError>(try_compiler_statement_instructions))
            {
                return std::get<BytecodeCompilerError>(try_compiler_statement_instructions);
            }
            auto statement_instructions = std::get<InstructionsVec>(try_compiler_statement_instructions);

            instructions.insert(instructions.end(), statement_instructions.begin(), statement_instructions.end());
        }

        return instructions;
    }
}