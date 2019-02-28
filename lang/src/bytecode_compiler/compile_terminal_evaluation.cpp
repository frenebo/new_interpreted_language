#include "./bytecode_compiler.hpp"

namespace bytecode_compiler
{
        BytecodeCompiler::InstructionsOrErr instruction_to_evaluate_number_expression_to_stack(const syntax_tree::terminal_expressions::NumberExpression & number_expression)
    {
        std::vector<bytecode::instructions::InstructionContainer> instructions;

        if (number_expression.number_type() == syntax_tree::terminal_expressions::NumberExpression::NumberType::FLOAT)
        {
            float val = std::stof(number_expression.number_string());
            instructions.push_back(bytecode::instructions::InstructionContainer(
                bytecode::instructions::StackFloatPushConst(val)
            ));
        }
        else if (number_expression.number_type() == syntax_tree::terminal_expressions::NumberExpression::NumberType::INT)
        {
            int val = std::stoi(number_expression.number_string());
            instructions.push_back(bytecode::instructions::InstructionContainer(
                bytecode::instructions::StackIntegerPushConst(val)
            ));
        }
        else
        {
            return BytecodeCompilerError("Unimplemented number type (number terminal expression compilation)\n");
        }

        return instructions;
    }

    BytecodeCompiler::InstructionsOrErr instruction_to_evaluate_identifier_to_stack(const syntax_tree::terminal_expressions::IdentifierExpression & identifier_expression)
    {
        std::vector<bytecode::instructions::InstructionContainer> instructions;

        instructions.push_back(bytecode::instructions::InstructionContainer(
            bytecode::instructions::StackLoadFromVariable(identifier_expression.identifier_string())
        ));

        return instructions;
    }
    
    BytecodeCompiler::InstructionsOrErr BytecodeCompiler::compile_terminal_evaluation(const syntax_tree::terminal_expressions::TerminalExpressionContainer & terminal_expression)
    {
        auto contained_exp = terminal_expression.contained_terminal_exp();
        if (std::holds_alternative<syntax_tree::terminal_expressions::IdentifierExpression>(contained_exp))
        {
            auto identifier_exp = std::get<syntax_tree::terminal_expressions::IdentifierExpression>(contained_exp);

            return instruction_to_evaluate_identifier_to_stack(identifier_exp);
        }
        else if (std::holds_alternative<syntax_tree::terminal_expressions::NumberExpression>(contained_exp))
        {
            auto number_exp = std::get<syntax_tree::terminal_expressions::NumberExpression>(contained_exp);

            return instruction_to_evaluate_number_expression_to_stack(number_exp);
        }
        else
        {
            return BytecodeCompilerError("Compiler: Unimplemented terminal expression\n");
        }
    }
}