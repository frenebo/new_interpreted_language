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

        std::vector<bytecode::instructions::InstructionContainer> else_instructions;
        // Optional else block code
        if (if_statement.else_block().has_value())
        {

            const auto & else_block = *if_statement.else_block();

            if (std::holds_alternative<syntax_tree::statements::PlainElseBlock>(else_block))
            {
                BytecodeCompiler::InstructionsOrErr try_compile_plain_else_instructions = compile_statement_series(
                    std::get<syntax_tree::statements::PlainElseBlock>(else_block).body_statement_series()
                );
                if (std::holds_alternative<BytecodeCompilerError>(try_compile_plain_else_instructions))
                {
                    return std::get<BytecodeCompilerError>(try_compile_plain_else_instructions);
                }

                auto plain_else_instructions = std::get<BytecodeCompiler::InstructionsVec>(try_compile_plain_else_instructions);

                else_instructions.insert(else_instructions.end(), plain_else_instructions.begin(), plain_else_instructions.end());
            }
            else if (std::holds_alternative<syntax_tree::statements::ElseIfBlock>(else_block))
            {
                BytecodeCompiler::InstructionsOrErr try_compile_else_if_block = compile_if_statement(
                    std::get<syntax_tree::statements::ElseIfBlock>(else_block).if_statement()
                );
                if (std::holds_alternative<BytecodeCompilerError>(try_compile_else_if_block))
                {
                    return std::get<BytecodeCompilerError>(try_compile_else_if_block);
                }

                auto else_if_instructions = std::get<BytecodeCompiler::InstructionsVec>(try_compile_else_if_block);

                else_instructions.insert(else_instructions.end(), else_if_instructions.begin(), else_if_instructions.end());
            }
            else
            {
                return BytecodeCompilerError("Unimplemented else block type");
            }
        }
        else
        {
            // Else instruction vector remains empty if there is no else block
        }

        // go to the instruction right after the end of the if body, and the instruction that skips the else body
        instructions.push_back(bytecode::instructions::InstructionContainer(
            bytecode::instructions::GotoRelativePosition(if_body_instructions.size() + 2)
        ));

        // if body instructions
        instructions.insert(instructions.end(), if_body_instructions.begin(), if_body_instructions.end());

        // If the condition evaluates as true, at the end of the if section if the if-else block, skip past the else section
        instructions.push_back(bytecode::instructions::InstructionContainer(
            bytecode::instructions::GotoRelativePosition(else_instructions.size() + 1)
        ));

        // Insert else body instructions. Inserts nothing if else_instructions is empty
        instructions.insert(instructions.end(), else_instructions.begin(), else_instructions.end());

        return instructions;
    }
}