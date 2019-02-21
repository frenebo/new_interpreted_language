#include <iostream>
#include <utility>
#include <algorithm>

#include "./bytecode_compiler.hpp"

namespace bytecode_compiler
{
    BytecodeCompiler::BytecodeCompiler()
    {
    }

    std::vector<bytecode::instructions::InstructionContainer>
    BytecodeCompiler::compile_program(const syntax_tree::statement_series::StatementSeries & statement_series)
    {
        std::vector<bytecode::instructions::InstructionContainer> instructions;

        for (const syntax_tree::statements::StatementContainer & statement : statement_series.statements())
        {
            std::vector<bytecode::instructions::InstructionContainer> statement_instructions =
                compile_statement_container(statement);
            
            instructions.insert(instructions.end(), statement_instructions.begin(), statement_instructions.end());
        }

        return instructions;
    }

    std::vector<bytecode::instructions::InstructionContainer>
    BytecodeCompiler::compile_statement_container(const syntax_tree::statements::StatementContainer & statement_container)
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
        else if (std::holds_alternative<syntax_tree::statements::AssignmentStatement>(contained_statement))
        {
            return compile_assignment_statement(std::get<syntax_tree::statements::AssignmentStatement>(contained_statement));
        }
        else
        {
            std::cout << "Unimplemented statement compile\n";
            exit(1);
        }
    }

    std::vector<bytecode::instructions::InstructionContainer>
    BytecodeCompiler::compile_assignment_statement(const syntax_tree::statements::AssignmentStatement & assignment_statement)
    {
        auto instructions = instructions_to_evaluate_compound_exp_to_stack(assignment_statement.assigned_exp());

        instructions.push_back(bytecode::instructions::InstructionContainer(
            bytecode::instructions::StackStoreToVariable(assignment_statement.var_name())
        ));

        return instructions;
    }

    std::vector<bytecode::instructions::InstructionContainer>
    BytecodeCompiler::compile_compound_expression_statement(const syntax_tree::statements::CompoundExpressionStatement & compound_expression_statement)
    {
        auto instructions = instructions_to_evaluate_compound_exp_to_stack(compound_expression_statement.compound_exp());

        // get rid of the resulting value
        instructions.push_back(bytecode::instructions::InstructionContainer(
            bytecode::instructions::StackPop()
        ));
        
        return instructions;
    }

    std::vector<bytecode::instructions::InstructionContainer>
    BytecodeCompiler::compile_print_statement(const syntax_tree::statements::PrintStatement & print_statement)
    {
        auto instructions = instructions_to_evaluate_compound_exp_to_stack(print_statement.exp_to_print());

        // print the resulting value
        instructions.push_back(bytecode::instructions::InstructionContainer(
            bytecode::instructions::StackPrint()
        ));

        return instructions;
    }

    int op_type_priority(syntax_tree::compound_expression::OperatorType op_type)
    {
        switch (op_type)
        {
            case syntax_tree::compound_expression::OperatorType::MINUS_OP:
            case syntax_tree::compound_expression::OperatorType::PLUS_OP:
                return 0;
            case syntax_tree::compound_expression::OperatorType::MULT_OP:
            case syntax_tree::compound_expression::OperatorType::DIV_OP:
                return 1;
        }
    }

    std::vector<bytecode::instructions::InstructionContainer>
    BytecodeCompiler::instructions_to_evaluate_compound_exp_to_stack(const syntax_tree::compound_expression::CompoundExpression & compound_exp)
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
        
        // create instructions to push first terminal to stack
        std::vector<bytecode::instructions::InstructionContainer> first_terminal_instructions =
            instructions_to_evaluate_possibly_prefixed_terminal_to_stack(possibly_prefixed_terminals[0]);
        // insert instructions to push first terminal to stack
        instructions.insert(instructions.end(), first_terminal_instructions.begin(), first_terminal_instructions.end());

        std::vector<syntax_tree::compound_expression::OperatorType> postponed_ops;
        
        for (unsigned int operator_idx = 0; operator_idx < op_types.size(); operator_idx++)
        {
            // push this terminal to stack
            std::vector<bytecode::instructions::InstructionContainer> evaluate_terminal_instructions =
                instructions_to_evaluate_possibly_prefixed_terminal_to_stack(possibly_prefixed_terminals[operator_idx + 1]);
            
            instructions.insert(instructions.end(), evaluate_terminal_instructions.begin(), evaluate_terminal_instructions.end());
            
            // priority of this operator
            int this_op_priority = op_type_priority(op_types[operator_idx]);

            if (postponed_ops.size() != 0)
            {
                int last_postponed_priority = postponed_ops.back();

                // execute all postponed if the last has an equal (left-to-right precendence)
                // or higher priority than the current
                if (last_postponed_priority >= this_op_priority)
                {
                    while (postponed_ops.size() != 0)
                    {
                        instructions.push_back(
                            instruction_for_stack_operation(postponed_ops.back())
                        );
                        postponed_ops.pop_back();
                    }
                }
            }

            if (operator_idx != op_types.size() - 1)
            {
                int next_op_priority = op_type_priority(op_types[operator_idx + 1]);

                if (this_op_priority < next_op_priority)
                {
                    postponed_ops.push_back(op_types[operator_idx]);
                    continue;
                }
            }
            
            instructions.push_back(instruction_for_stack_operation(op_types[operator_idx]));
        }

        // add instructions for postponed ops while these exist
        while (postponed_ops.size() != 0)
        {
            instructions.push_back(
                instruction_for_stack_operation(postponed_ops.back())
            );
            postponed_ops.pop_back();
        }

        return instructions;
    }
    
    bytecode::instructions::InstructionContainer
    BytecodeCompiler::instruction_for_stack_operation(syntax_tree::compound_expression::OperatorType op_type)
    {
        if (op_type == syntax_tree::compound_expression::OperatorType::DIV_OP)
        {
            return bytecode::instructions::InstructionContainer(
                bytecode::instructions::StackDivide()
            );
        }
        else if (op_type == syntax_tree::compound_expression::OperatorType::MINUS_OP)
        {
            return bytecode::instructions::InstructionContainer(
                bytecode::instructions::StackSubtract()
            );
        }
        else if (op_type == syntax_tree::compound_expression::OperatorType::MULT_OP)
        {
            return bytecode::instructions::InstructionContainer(
                bytecode::instructions::StackMultiply()
            );
        }
        else if (op_type == syntax_tree::compound_expression::OperatorType::PLUS_OP)
        {
            return bytecode::instructions::InstructionContainer(
                bytecode::instructions::StackAdd()
            );
        }
        else
        {
            std::cout << "Unimplemented operation type\n";
            // placeholder
            exit(1);
        }
    }

    std::vector<bytecode::instructions::InstructionContainer>
    BytecodeCompiler::instructions_to_evaluate_possibly_prefixed_terminal_to_stack(const syntax_tree::compound_expression::PossiblyPrefixedTerminal & possibly_prefixed_terminal_expression)
    {
        auto instructions = instructions_to_evaluate_terminal_to_stack(possibly_prefixed_terminal_expression.terminal_exp_container());

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
                std::cout << "Compiler: unimplemented terminal value prefix\n";
            }
        }

        return instructions;
    }

    std::vector<bytecode::instructions::InstructionContainer>
    BytecodeCompiler::instructions_to_evaluate_terminal_to_stack(const syntax_tree::terminal_expressions::TerminalExpressionContainer & terminal_expression)
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
            std::cout << "Unimplemented terminal expression\n";
            return std::vector<bytecode::instructions::InstructionContainer>();
        }
    }

    std::vector<bytecode::instructions::InstructionContainer>
    BytecodeCompiler::instruction_to_evaluate_number_expression_to_stack(const syntax_tree::terminal_expressions::NumberExpression & number_expression)
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
            std::cout << "Unimplemented number type (number terminal expression compilation)\n";
        }
        
        return instructions;
    }
    
    std::vector<bytecode::instructions::InstructionContainer>
    BytecodeCompiler::instruction_to_evaluate_identifier_to_stack(const syntax_tree::terminal_expressions::IdentifierExpression & identifier_expression)
    {
        std::vector<bytecode::instructions::InstructionContainer> instructions;

        instructions.push_back(bytecode::instructions::InstructionContainer(
            bytecode::instructions::StackLoadFromVariable(identifier_expression.identifier_string())
        ));

        return instructions;
    }
}