#include "./bytecode_compiler.hpp"

namespace bytecode_compiler
{
    BytecodeCompiler::InstructionsOrErr BytecodeCompiler::compile_for_statement(const syntax_tree::statements::ForLoopStatement & for_loop)
    {
        auto try_compile_setup_exp =
            compile_compound_exp_evaluation(for_loop.setup_expression());
        if (std::holds_alternative<BytecodeCompilerError>(try_compile_setup_exp))
        {
            return std::get<BytecodeCompilerError>(try_compile_setup_exp);
        }
        
        auto try_compile_condition_exp =
            compile_compound_exp_evaluation(for_loop.condition_expression());
        if (std::holds_alternative<BytecodeCompilerError>(try_compile_condition_exp))
        {
            return std::get<BytecodeCompilerError>(try_compile_condition_exp);
        }
        
        auto try_compile_increment_exp =
            compile_compound_exp_evaluation(for_loop.increment_expression());
        if (std::holds_alternative<BytecodeCompilerError>(try_compile_increment_exp))
        {
            return std::get<BytecodeCompilerError>(try_compile_increment_exp);
        }
        
        auto try_compile_for_loop_body =
            compile_statement_series(for_loop.loop_body());
        if (std::holds_alternative<BytecodeCompilerError>(try_compile_for_loop_body))
        {
            return std::get<BytecodeCompilerError>(try_compile_for_loop_body);
        }

        InstructionsVec setup_exp_instructions = std::get<InstructionsVec>(try_compile_setup_exp);
        InstructionsVec condition_exp_instructions = std::get<InstructionsVec>(try_compile_condition_exp);
        InstructionsVec increment_exp_instructions = std::get<InstructionsVec>(try_compile_increment_exp);
        InstructionsVec loop_body_instructions  = std::get<InstructionsVec>(try_compile_for_loop_body);

        InstructionsVec instructions;

        push_instructions(instructions, setup_exp_instructions);
        push_instructions(instructions, condition_exp_instructions);
        instructions.push_back(bytecode::instructions::InstructionContainer(
            bytecode::instructions::SkipNextInstructionIfStackValueTruthy()
        ));
        unsigned long dist_to_skip_to_after_increment =
            loop_body_instructions.size() + // gets to last instruction of body
            increment_exp_instructions.size() + // gets to last instruction of increment
            2; // gets to the skip to begin of loop, then goes one more
        instructions.push_back(bytecode::instructions::InstructionContainer(
            bytecode::instructions::GotoRelativePosition(dist_to_skip_to_after_increment)
        ));
        push_instructions(instructions, loop_body_instructions);
        push_instructions(instructions, increment_exp_instructions);
        // goto beginning of loop
        unsigned long dist_to_condition_instruction = -(
            increment_exp_instructions.size() +// gets to beginning of increment exp
            loop_body_instructions.size() + // gets to beginning of loop body
            1 + // gets to the skip to condition skip
            1 +// gets to the SkipNextInstructionifStackValueTruthy instruction
            condition_exp_instructions.size() // gets to the beginning of condition evaluation
            );

        instructions.push_back(bytecode::instructions::InstructionContainer(
            bytecode::instructions::GotoRelativePosition(dist_to_condition_instruction)
        ));
        // instructions.push_back
        // push_instructions(instructions, setup_exp.)
        
        return instructions;
    }
}