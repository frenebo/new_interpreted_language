#include <iostream>
#include <utility>
#include <algorithm>

#include "./bytecode_compiler.hpp"

namespace bytecode_compiler
{
    void BytecodeCompiler::push_instructions(InstructionsVec & target_vec, const InstructionsVec & source_vec)
    {
        target_vec.insert(target_vec.end(), source_vec.begin(), source_vec.end());
    }
    
    BytecodeCompiler::BytecodeCompiler()
    {
    }


    BytecodeCompiler::BytecodeCompiler::InstructionsOrErr BytecodeCompiler::compile_statement_container(const syntax_tree::statements::StatementContainer & statement_container)
    {
        auto contained_statement = statement_container.contained_statement();

        if (std::holds_alternative<syntax_tree::statements::CompoundExpressionStatement>(contained_statement))
        {
            return compile_compound_expression_statement(std::get<syntax_tree::statements::CompoundExpressionStatement>(contained_statement));
        }
        else if (std::holds_alternative<syntax_tree::statements::PrintStatement>(contained_statement))
        {
            return compile_print_statement(std::get<syntax_tree::statements::PrintStatement>(contained_statement));
        }
        else if (std::holds_alternative<syntax_tree::statements::IfStatement>(contained_statement))
        {
            return compile_if_statement(std::get<syntax_tree::statements::IfStatement>(contained_statement));
        }
        else
        {
            return BytecodeCompilerError("Unimplemented statement compile\n");
        }
    }

    BytecodeCompiler::InstructionsOrErr BytecodeCompiler::compile_if_statement(const syntax_tree::statements::IfStatement & if_statement)
    {
        auto try_compile_condition_evaluate_instructions =
            instructions_to_evaluate_compound_exp_to_stack(if_statement.if_condition());
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

    BytecodeCompiler::InstructionsOrErr BytecodeCompiler::compile_compound_expression_statement(const syntax_tree::statements::CompoundExpressionStatement & compound_expression_statement)
    {
        auto try_compile_exp_instructions = instructions_to_evaluate_compound_exp_to_stack(compound_expression_statement.compound_exp());
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

    BytecodeCompiler::InstructionsOrErr BytecodeCompiler::compile_print_statement(const syntax_tree::statements::PrintStatement & print_statement)
    {
        auto try_parse_instructions = instructions_to_evaluate_compound_exp_to_stack(print_statement.exp_to_print());

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

    std::variant<int, BytecodeCompilerError> op_type_priority(syntax_tree::compound_expression::OperatorType op_type)
    {
        switch (op_type)
        {
            case syntax_tree::compound_expression::OperatorType::ASSIGNMENT_OP:
                return 0;
            case syntax_tree::compound_expression::OperatorType::MINUS_OP:
            case syntax_tree::compound_expression::OperatorType::PLUS_OP:
                return 1;
            case syntax_tree::compound_expression::OperatorType::MULT_OP:
            case syntax_tree::compound_expression::OperatorType::DIV_OP:
                return 2;
        }
        return BytecodeCompilerError("Unimplemented op type priority\n");
    }

    BytecodeCompiler::InstructionsOrErr BytecodeCompiler::instructions_to_evaluate_compound_exp_to_stack(const syntax_tree::compound_expression::CompoundExpression & compound_exp)
    {
        std::vector<syntax_tree::compound_expression::PossiblyPrefixedTerminal> possibly_prefixed_terminals;
        std::vector<syntax_tree::compound_expression::OperatorType> op_types;

        possibly_prefixed_terminals.push_back(compound_exp.start_exp());

        for (const syntax_tree::compound_expression::CompoundExpressionSuffix & suffix : compound_exp.suffixes())
        {
            possibly_prefixed_terminals.push_back(suffix.terminal_exp());

            op_types.push_back(suffix.op_type());
        }

        std::vector<bytecode::instructions::InstructionContainer> instructions;

        std::vector<int> op_type_priorities;
        for (syntax_tree::compound_expression::OperatorType op_type : op_types)
        {
            auto try_get_op_type = op_type_priority(op_type);
            if (std::holds_alternative<BytecodeCompilerError>(try_get_op_type))
            {
                return std::get<BytecodeCompilerError>(try_get_op_type);
            }
            int op_type_priority = std::get<int>(try_get_op_type);
            op_type_priorities.push_back(op_type_priority);
        }

        // create instructions to push first terminal to stack
        auto try_parse_first_terminal_instructions =
            instructions_to_evaluate_possibly_prefixed_terminal_to_stack(possibly_prefixed_terminals[0]);
        if (std::holds_alternative<BytecodeCompilerError>(try_parse_first_terminal_instructions))
        {
            return std::get<BytecodeCompilerError>(try_parse_first_terminal_instructions);
        }
        InstructionsVec first_terminal_instructions = std::get<InstructionsVec>(try_parse_first_terminal_instructions);
        
        // insert instructions to push first terminal to stack
        instructions.insert(instructions.end(), first_terminal_instructions.begin(), first_terminal_instructions.end());

        std::vector<syntax_tree::compound_expression::OperatorType> postponed_ops;

        for (unsigned int operator_idx = 0; operator_idx < op_types.size(); operator_idx++)
        {
            // push the terminal to the stack
            InstructionsOrErr try_compile_terminal =
                instructions_to_evaluate_possibly_prefixed_terminal_to_stack(possibly_prefixed_terminals[operator_idx + 1]);
            
            if (std::holds_alternative<BytecodeCompilerError>(try_compile_terminal))
            {
                return std::get<BytecodeCompilerError>(try_compile_terminal);
            }
            InstructionsVec evaluate_terminal_instructions = std::get<InstructionsVec>(try_compile_terminal);

            push_instructions(instructions, evaluate_terminal_instructions);

            // priority of this operator
            int this_op_priority = op_type_priorities[operator_idx];

            if (postponed_ops.size() != 0)
            {
                int last_postponed_priority = postponed_ops.back();

                // execute all postponed if the last has an equal (left-to-right precendence)
                // or higher priority than the current
                if (last_postponed_priority >= this_op_priority)
                {
                    while (postponed_ops.size() != 0)
                    {
                        InstructionsOrErr try_compile_instructions_for_op = instructions_for_stack_operation(postponed_ops.back());
                        if (std::holds_alternative<BytecodeCompilerError>(try_compile_instructions_for_op))
                        {
                            return std::get<BytecodeCompilerError>(try_compile_instructions_for_op);
                        }
                        InstructionsVec instructions_for_op = std::get<InstructionsVec>(try_compile_instructions_for_op);

                        push_instructions(instructions, instructions_for_op);
                        postponed_ops.pop_back();
                    }
                }
            }

            if (operator_idx != op_types.size() - 1)
            {
                int next_op_priority = op_type_priorities[operator_idx + 1];

                if (this_op_priority < next_op_priority)
                {
                    postponed_ops.push_back(op_types[operator_idx]);
                    continue;
                }
            }

            InstructionsOrErr try_compile_instructions_for_op = instructions_for_stack_operation(op_types[operator_idx]);
            if (std::holds_alternative<BytecodeCompilerError>(try_compile_instructions_for_op))
            {
                return std::get<BytecodeCompilerError>(try_compile_instructions_for_op);
            }
            InstructionsVec instructions_for_op = std::get<InstructionsVec>(try_compile_instructions_for_op);
            push_instructions(instructions, instructions_for_op);
        }

        // add instructions for postponed ops while these exist
        while (postponed_ops.size() != 0)
        {
            auto try_compile_instructions_for_op = instructions_for_stack_operation(postponed_ops.back());
            if (std::holds_alternative<BytecodeCompilerError>(try_compile_instructions_for_op))
            {
                return std::get<BytecodeCompilerError>(try_compile_instructions_for_op);
            }
            InstructionsVec instructions_for_op = std::get<InstructionsVec>(try_compile_instructions_for_op);
            
            push_instructions(instructions, instructions_for_op);
            
            postponed_ops.pop_back();
        }

        return instructions;
    }

    BytecodeCompiler::InstructionsOrErr BytecodeCompiler::instructions_for_stack_operation(syntax_tree::compound_expression::OperatorType op_type)
    {
        std::vector<bytecode::instructions::InstructionContainer> instructions;
        if (op_type == syntax_tree::compound_expression::OperatorType::DIV_OP)
        {
            instructions.push_back(bytecode::instructions::InstructionContainer(
                bytecode::instructions::StackDivide()
            ));
        }
        else if (op_type == syntax_tree::compound_expression::OperatorType::MINUS_OP)
        {
            instructions.push_back(bytecode::instructions::InstructionContainer(
                bytecode::instructions::StackSubtract()
            ));
        }
        else if (op_type == syntax_tree::compound_expression::OperatorType::MULT_OP)
        {
            instructions.push_back(bytecode::instructions::InstructionContainer(
                bytecode::instructions::StackMultiply()
            ));
        }
        else if (op_type == syntax_tree::compound_expression::OperatorType::PLUS_OP)
        {
            instructions.push_back(bytecode::instructions::InstructionContainer(
                bytecode::instructions::StackAdd()
            ));
        }
        else if (op_type == syntax_tree::compound_expression::OperatorType::ASSIGNMENT_OP)
        {
            return BytecodeCompilerError("Compiler: Unimplemented assignment operation\n");
        }
        else
        {
            return BytecodeCompilerError("Compiler: Unimplemented operation type\n");
        }

        return instructions;
    }

    BytecodeCompiler::InstructionsOrErr BytecodeCompiler::instructions_to_evaluate_possibly_prefixed_terminal_to_stack(const syntax_tree::compound_expression::PossiblyPrefixedTerminal & possibly_prefixed_terminal_expression)
    {
        InstructionsOrErr try_compile_terminal_instructions = instructions_to_evaluate_terminal_to_stack(possibly_prefixed_terminal_expression.terminal_exp_container());
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

    BytecodeCompiler::InstructionsOrErr BytecodeCompiler::instructions_to_evaluate_terminal_to_stack(const syntax_tree::terminal_expressions::TerminalExpressionContainer & terminal_expression)
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

    BytecodeCompiler::InstructionsOrErr BytecodeCompiler::instruction_to_evaluate_number_expression_to_stack(const syntax_tree::terminal_expressions::NumberExpression & number_expression)
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

    BytecodeCompiler::InstructionsOrErr BytecodeCompiler::instruction_to_evaluate_identifier_to_stack(const syntax_tree::terminal_expressions::IdentifierExpression & identifier_expression)
    {
        std::vector<bytecode::instructions::InstructionContainer> instructions;

        instructions.push_back(bytecode::instructions::InstructionContainer(
            bytecode::instructions::StackLoadFromVariable(identifier_expression.identifier_string())
        ));

        return instructions;
    }
}
