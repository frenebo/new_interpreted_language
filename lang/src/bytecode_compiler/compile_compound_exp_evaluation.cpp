#include <memory>
#include <variant>
#include <algorithm>
#include <iostream>

#include "./bytecode_compiler.hpp"
#include "./compound_exp_tree/compound_exp_tree.hpp"

namespace bytecode_compiler
{
    std::variant<int, BytecodeCompilerError> op_type_priority(syntax_tree::compound_expression::OperatorType op_type)
    {
        switch (op_type)
        {
            case syntax_tree::compound_expression::OperatorType::ASSIGNMENT_OP:
            case syntax_tree::compound_expression::OperatorType::MINUS_EQUALS_ASSIGNMENT_OP:
            case syntax_tree::compound_expression::OperatorType::PLUS_EQUALS_ASSIGNMENT_OP:
                return 0;
            case syntax_tree::compound_expression::OperatorType::OR_OP:
                return 1;
            case syntax_tree::compound_expression::OperatorType::AND_OP:
                return 2;
            case syntax_tree::compound_expression::OperatorType::EQUALITY_COMPARISON_OP:
                return 3;
            case syntax_tree::compound_expression::OperatorType::LESS_THAN_OP:
            case syntax_tree::compound_expression::OperatorType::LESS_THAN_OR_EQUAL_OP:
            case syntax_tree::compound_expression::OperatorType::MORE_THAN_OP:
            case syntax_tree::compound_expression::OperatorType::MORE_THAN_OR_EQUAL_OP:
                return 4;
            case syntax_tree::compound_expression::OperatorType::MINUS_OP:
            case syntax_tree::compound_expression::OperatorType::PLUS_OP:
                return 5;
            case syntax_tree::compound_expression::OperatorType::MULT_OP:
            case syntax_tree::compound_expression::OperatorType::DIV_OP:
            case syntax_tree::compound_expression::OperatorType::MODULO_OP:
                return 6;
        }
        return BytecodeCompilerError("Unimplemented op type priority\n");
    }

    std::variant<compound_exp_tree::CompoundExpValueNode, BytecodeCompilerError>
    convert_exp_node_to_value_node(const compound_exp_tree::CompoundExpNodeContainer & node_container);

    std::variant<compound_exp_tree::CompoundExpNodeContainer, BytecodeCompilerError>
    node_for_terminal(const syntax_tree::terminal_expressions::TerminalExpressionContainer & terminal)
    {
        const syntax_tree::terminal_expressions::TerminalExpressionContainer::VariantTerminalExp & contained =
            terminal.contained_terminal_exp();

        if (std::holds_alternative<syntax_tree::terminal_expressions::IdentifierExpression>(contained))
        {
            auto identifier_exp = std::get<syntax_tree::terminal_expressions::IdentifierExpression>(contained);

            return compound_exp_tree::CompoundExpNodeContainer(
                compound_exp_tree::CompoundExpVariableNode(identifier_exp.identifier_string())
            );
        }
        else if (std::holds_alternative<syntax_tree::terminal_expressions::NumberExpression>(contained))
        {
            auto number_exp = std::get<syntax_tree::terminal_expressions::NumberExpression>(contained);
            std::vector<bytecode::instructions::InstructionContainer> instructions;

            if (number_exp.number_type() == syntax_tree::terminal_expressions::NumberExpression::NumberType::INT)
            {
                int push_val = std::stoi(number_exp.number_string());
                instructions.push_back(bytecode::instructions::InstructionContainer(
                    bytecode::instructions::StackIntegerPushConst(push_val)
                ));

                return compound_exp_tree::CompoundExpNodeContainer(
                    compound_exp_tree::CompoundExpValueNode(instructions)
                );
            }
            else if (number_exp.number_type() == syntax_tree::terminal_expressions::NumberExpression::NumberType::FLOAT)
            {
                float push_val = std::stof(number_exp.number_string());
                instructions.push_back(bytecode::instructions::InstructionContainer(
                    bytecode::instructions::StackFloatPushConst(push_val)
                ));

                return compound_exp_tree::CompoundExpNodeContainer(
                    compound_exp_tree::CompoundExpValueNode(instructions)
                );
            }
            else
            {
                return BytecodeCompilerError("Unimplemented terminal expression compile type");
            }
        }
        else if (std::holds_alternative<syntax_tree::terminal_expressions::BoolLiteralExpression>(contained))
        {
            auto bool_exp = std::get<syntax_tree::terminal_expressions::BoolLiteralExpression>(contained);
            BytecodeCompiler::InstructionsVec instructions;

            instructions.push_back(bytecode::instructions::InstructionContainer(
                bytecode::instructions::StackBoolPushConst(bool_exp.value())
            ));

            return compound_exp_tree::CompoundExpNodeContainer(
                compound_exp_tree::CompoundExpValueNode(instructions)
            );
        }
        else if (std::holds_alternative<syntax_tree::terminal_expressions::StringLiteralExpression>(contained))
        {
            auto string_exp = std::get<syntax_tree::terminal_expressions::StringLiteralExpression>(contained);
            BytecodeCompiler::InstructionsVec instructions;
            instructions.push_back(bytecode::instructions::InstructionContainer(
                bytecode::instructions::StackStringPushConst(string_exp.string_text())
            ));

            return compound_exp_tree::CompoundExpNodeContainer(
                compound_exp_tree::CompoundExpValueNode(instructions)
            );
        }
        else
        {
            return BytecodeCompilerError("Unimplemented terminal node compilation");
        }
    }

    std::variant<compound_exp_tree::CompoundExpValueNode, BytecodeCompilerError>
    convert_exp_operation_node_to_value_node(const compound_exp_tree::CompoundExpOpNode & exp_node)
    {
        const compound_exp_tree::CompoundExpNodeContainer & lhs =
            exp_node.lhs();
        syntax_tree::compound_expression::OperatorType op_type = exp_node.op_type();
        const compound_exp_tree::CompoundExpNodeContainer & rhs =
            exp_node.rhs();

        // the assignment op is the one operation where the left side may start of as undefined.
        // if the statement is "a = 1", and a is a new variable, you can't evaluate the left hand side (a)
        if (
            op_type == syntax_tree::compound_expression::OperatorType::ASSIGNMENT_OP ||
            op_type == syntax_tree::compound_expression::OperatorType::MINUS_EQUALS_ASSIGNMENT_OP ||
            op_type == syntax_tree::compound_expression::OperatorType::PLUS_EQUALS_ASSIGNMENT_OP)
        {
            if (!std::holds_alternative<compound_exp_tree::CompoundExpVariableNode>(lhs.contained()))
            {
                return BytecodeCompilerError("Invalid left side of assignment: must be variable");
            }
            std::string variable_name = std::get<compound_exp_tree::CompoundExpVariableNode>(lhs.contained()).variable_name();

            auto try_convert_rhs_to_value_node = convert_exp_node_to_value_node(rhs.contained());
            if (std::holds_alternative<BytecodeCompilerError>(try_convert_rhs_to_value_node))
            {
                return std::get<BytecodeCompilerError>(try_convert_rhs_to_value_node);
            }

            BytecodeCompiler::InstructionsVec rhs_evaluate_instructions = std::get<compound_exp_tree::CompoundExpValueNode>(try_convert_rhs_to_value_node).instructions();

            std::vector<bytecode::instructions::InstructionContainer> instructions;

            if (op_type == syntax_tree::compound_expression::OperatorType::ASSIGNMENT_OP)
            {
                // the operation starts off with evaluating the right hand side
                BytecodeCompiler::push_instructions(instructions, rhs_evaluate_instructions);
            }
            else if (op_type == syntax_tree::compound_expression::OperatorType::MINUS_EQUALS_ASSIGNMENT_OP)
            {
                instructions.push_back(bytecode::instructions::InstructionContainer(
                    bytecode::instructions::StackLoadFromVariable(variable_name)
                ));
                BytecodeCompiler::push_instructions(instructions, rhs_evaluate_instructions);
                instructions.push_back(bytecode::instructions::InstructionContainer(
                    bytecode::instructions::StackSubtract()
                ));
            }
            else if (op_type == syntax_tree::compound_expression::OperatorType::PLUS_EQUALS_ASSIGNMENT_OP)
            {
                instructions.push_back(bytecode::instructions::InstructionContainer(
                    bytecode::instructions::StackLoadFromVariable(variable_name)
                ));
                BytecodeCompiler::push_instructions(instructions, rhs_evaluate_instructions);
                instructions.push_back(bytecode::instructions::InstructionContainer(
                    bytecode::instructions::StackAdd()
                ));
            }
            else
            {
                return BytecodeCompilerError("Unimplemented assignment operator compile");
            }

            instructions.push_back(bytecode::instructions::InstructionContainer(
                bytecode::instructions::StackDuplicate()
            ));
            instructions.push_back(bytecode::instructions::InstructionContainer(
                bytecode::instructions::StackStoreToVariable(variable_name)
            ));

            return instructions;
        }
        else
        {
            auto try_convert_lhs_to_value_node = convert_exp_node_to_value_node(lhs.contained());
            if (std::holds_alternative<BytecodeCompilerError>(try_convert_lhs_to_value_node))
            {
                return std::get<BytecodeCompilerError>(try_convert_lhs_to_value_node);
            }

            auto try_convert_rhs_to_value_node = convert_exp_node_to_value_node(rhs.contained());
            if (std::holds_alternative<BytecodeCompilerError>(try_convert_rhs_to_value_node))
            {
                return std::get<BytecodeCompilerError>(try_convert_rhs_to_value_node);
            }

            BytecodeCompiler::InstructionsVec lhs_evaluate_instructions =
                std::get<compound_exp_tree::CompoundExpValueNode>(try_convert_lhs_to_value_node).instructions();
            BytecodeCompiler::InstructionsVec rhs_evaluate_instructions =
                std::get<compound_exp_tree::CompoundExpValueNode>(try_convert_rhs_to_value_node).instructions();

            std::vector<bytecode::instructions::InstructionContainer> instructions;
            BytecodeCompiler::push_instructions(instructions, lhs_evaluate_instructions);
            BytecodeCompiler::push_instructions(instructions, rhs_evaluate_instructions);

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
            else if (op_type == syntax_tree::compound_expression::OperatorType::LESS_THAN_OP)
            {
                instructions.push_back(bytecode::instructions::InstructionContainer(
                    bytecode::instructions::StackCompareLessThan()
                ));
            }
            else if (op_type == syntax_tree::compound_expression::OperatorType::LESS_THAN_OR_EQUAL_OP)
            {
                instructions.push_back(bytecode::instructions::InstructionContainer(
                    bytecode::instructions::StackCompareLessThanOrEqualTo()
                ));
            }
            else if (op_type == syntax_tree::compound_expression::OperatorType::MORE_THAN_OP)
            {
                // more than is the same as not less than or equal to
                instructions.push_back(bytecode::instructions::InstructionContainer(
                    bytecode::instructions::StackCompareLessThanOrEqualTo()
                ));
                instructions.push_back(bytecode::instructions::InstructionContainer(
                    bytecode::instructions::StackApplyNot()
                ));
            }
            else if (op_type == syntax_tree::compound_expression::OperatorType::MORE_THAN_OR_EQUAL_OP)
            {
                // more than or equal to is the same as not less than
                instructions.push_back(bytecode::instructions::InstructionContainer(
                    bytecode::instructions::StackCompareLessThan()
                ));
                instructions.push_back(bytecode::instructions::InstructionContainer(
                    bytecode::instructions::StackApplyNot()
                ));
            }
            else if (op_type == syntax_tree::compound_expression::OperatorType::MODULO_OP)
            {
                instructions.push_back(bytecode::instructions::InstructionContainer(
                    bytecode::instructions::StackModuloOperation()
                ));
            }
            else if (op_type == syntax_tree::compound_expression::OperatorType::AND_OP)
            {
                instructions.push_back(bytecode::instructions::InstructionContainer(
                    bytecode::instructions::StackAndOperation()
                ));
            }
            else if (op_type == syntax_tree::compound_expression::OperatorType::OR_OP)
            {
                instructions.push_back(bytecode::instructions::InstructionContainer(
                    bytecode::instructions::StackOrOperation()
                ));
            }
            else
            {
                return BytecodeCompilerError("Unimplemented operator type compilation");
            }

            auto return_val_node = compound_exp_tree::CompoundExpValueNode (instructions);

            return return_val_node;
        }
    }

    std::variant<compound_exp_tree::CompoundExpValueNode, BytecodeCompilerError>
    convert_exp_node_to_value_node(const compound_exp_tree::CompoundExpNodeContainer & node_container)
    {
        const compound_exp_tree::CompoundExpNodeContainer::VariantCompoundExpNode & contained =
            node_container.contained();

        if (std::holds_alternative<compound_exp_tree::CompoundExpValueNode>(contained))
        {
            // nothing needs to be changed if it's already a value node
            return std::get<compound_exp_tree::CompoundExpValueNode>(contained);
        }
        else if (std::holds_alternative<compound_exp_tree::CompoundExpOpNode>(contained))
        {
            compound_exp_tree::CompoundExpOpNode op_node =
                std::get<compound_exp_tree::CompoundExpOpNode>(contained);

            return convert_exp_operation_node_to_value_node(op_node);
        }
        else if (std::holds_alternative<compound_exp_tree::CompoundExpVariableNode>(contained))
        {
            compound_exp_tree::CompoundExpVariableNode variable_node =
                std::get<compound_exp_tree::CompoundExpVariableNode>(contained);

            BytecodeCompiler::InstructionsVec instructions;
            instructions.push_back(bytecode::instructions::InstructionContainer(
                bytecode::instructions::StackLoadFromVariable(variable_node.variable_name())
            ));

            return compound_exp_tree::CompoundExpValueNode(instructions);
        }
        else
        {
            return BytecodeCompilerError("Unimplemented conversion to expression value node");
        }
    }

    std::variant<compound_exp_tree::CompoundExpNodeContainer, BytecodeCompilerError>
    node_for_possibly_prefixed_terminal(const syntax_tree::compound_expression::PossiblyPrefixedTerminal & possibly_prefixed_terminal)
    {
        auto try_compile_terminal = node_for_terminal(possibly_prefixed_terminal.terminal_exp_container());
        if (std::holds_alternative<BytecodeCompilerError>(try_compile_terminal))
        {
            return std::get<BytecodeCompilerError>(try_compile_terminal);
        }
        compound_exp_tree::CompoundExpNodeContainer compiled_terminal =
            std::get<compound_exp_tree::CompoundExpNodeContainer>(try_compile_terminal);

        if (!possibly_prefixed_terminal.possible_prefix_type().has_value())
        {
            return compiled_terminal;
        }
        else
        {
            syntax_tree::compound_expression::PrefixType prefix_type =
                *possibly_prefixed_terminal.possible_prefix_type();

            auto try_convert_terminal_to_value_node =
                convert_exp_node_to_value_node(compiled_terminal);

            if (std::holds_alternative<BytecodeCompilerError>(try_convert_terminal_to_value_node))
            {
                return std::get<BytecodeCompilerError>(try_convert_terminal_to_value_node);
            }

            const BytecodeCompiler::InstructionsVec & terminal_evaluate_instructions =
                std::get<compound_exp_tree::CompoundExpValueNode>(try_convert_terminal_to_value_node).instructions();

            // start off with these instructions, then apply the prefix
            BytecodeCompiler::InstructionsVec instructions = terminal_evaluate_instructions;

            if (prefix_type == syntax_tree::compound_expression::PrefixType::MINUS_PREFIX)
            {
                // multiply by negative one
                instructions.push_back(bytecode::instructions::InstructionContainer(
                    bytecode::instructions::StackIntegerPushConst(-1)
                ));
                instructions.push_back(bytecode::instructions::InstructionContainer(
                    bytecode::instructions::StackMultiply()
                ));

                compound_exp_tree::CompoundExpValueNode exp_value_node(instructions);

                return compound_exp_tree::CompoundExpNodeContainer(exp_value_node);
            }
            else
            {
                return BytecodeCompilerError("Unimplemented prefix type");
            }
        }
    }

    bool compare_priority_pairs(std::pair<size_t, int> left, std::pair<size_t, int> right)
    {
        return left.second <= right.second;
    }

    std::variant<std::vector<size_t>, BytecodeCompilerError>
    get_sorted_indices_of_op_type_vec(const std::vector<syntax_tree::compound_expression::OperatorType> & ops)
    {
        std::vector<std::pair<size_t, int>> indices_and_priorities;
        indices_and_priorities.reserve(ops.size());
        for (size_t i = 0; i < ops.size(); i++)
        {
            auto try_get_priority = op_type_priority(ops[i]);
            if (std::holds_alternative<BytecodeCompilerError>(try_get_priority))
            {
                return std::get<BytecodeCompilerError>(try_get_priority);
            }
            int priority = std::get<int>(try_get_priority);
            indices_and_priorities.push_back(std::make_pair(i, priority));
        }
        std::stable_sort(
            indices_and_priorities.begin(),
            indices_and_priorities.end(),
            compare_priority_pairs
        );

        std::vector<size_t> indices;
        indices.reserve(ops.size());
        for (const std::pair<size_t, int> & pair : indices_and_priorities)
        {
            indices.push_back(pair.first);
        }

        return indices;
    }

    BytecodeCompiler::InstructionsOrErr
    BytecodeCompiler::compile_compound_exp_evaluation(const syntax_tree::compound_expression::CompoundExpression & compound_exp)
    {
        // the goal is to collapse the exp nodes to nothing
        std::vector<compound_exp_tree::CompoundExpNodeContainer> exp_nodes;
        std::vector<syntax_tree::compound_expression::OperatorType> unprocessed_ops;

        // compound_exp
        // add the first terminal to exp_nodes
        auto try_compile_first_possibly_prefixed_terminal =
            node_for_possibly_prefixed_terminal(compound_exp.start_exp());
        if (std::holds_alternative<BytecodeCompilerError>(try_compile_first_possibly_prefixed_terminal))
        {
            return std::get<BytecodeCompilerError>(try_compile_first_possibly_prefixed_terminal);
        }
        exp_nodes.push_back(
            std::get<compound_exp_tree::CompoundExpNodeContainer>(try_compile_first_possibly_prefixed_terminal)
        );

        // add the other terminals and operations
        for (const syntax_tree::compound_expression::CompoundExpressionSuffix & suffix : compound_exp.suffixes())
        {
            // add the terminal to exp_nodes
            auto try_compile_prefixed_terminal =
                node_for_possibly_prefixed_terminal(suffix.terminal_exp());
            if (std::holds_alternative<BytecodeCompilerError>(try_compile_prefixed_terminal))
            {
                return std::get<BytecodeCompilerError>(try_compile_prefixed_terminal);
            }
            exp_nodes.push_back(
                std::get<compound_exp_tree::CompoundExpNodeContainer>(try_compile_prefixed_terminal)
            );

            // add the operation to unprocessed_ops
            unprocessed_ops.push_back(suffix.op_type());
        }

        std::vector<int> op_priorities_by_original_idx;
        op_priorities_by_original_idx.reserve(unprocessed_ops.size());
        for (size_t i = 0; i < unprocessed_ops.size(); i++)
        {
            auto try_get_priority = op_type_priority(unprocessed_ops[i]);
            if (std::holds_alternative<BytecodeCompilerError>(try_get_priority))
            {
                return std::get<BytecodeCompilerError>(try_get_priority);
            }
            int priority = std::get<int>(try_get_priority);
            op_priorities_by_original_idx.push_back(priority);
        }

        // to keep track of the new positions of operations
        std::vector<size_t> op_current_positions_by_original_idx;
        op_current_positions_by_original_idx.reserve(unprocessed_ops.size());
        for (size_t i = 0; i < unprocessed_ops.size(); i++)
        {
            op_current_positions_by_original_idx.push_back(i);
        }

        // the indices of sorted operations
        auto try_sort_indices = get_sorted_indices_of_op_type_vec(unprocessed_ops);
        if (std::holds_alternative<BytecodeCompilerError>(try_sort_indices))
        {
            return std::get<BytecodeCompilerError>(try_sort_indices);
        }
        std::vector<size_t> sorted_op_indices = std::get<std::vector<size_t>>(try_sort_indices);
        std::reverse(sorted_op_indices.begin(), sorted_op_indices.end());

        for (size_t orig_op_index : sorted_op_indices)
        {
            size_t op_index = op_current_positions_by_original_idx[orig_op_index];

            // get the left hand and right hand sides
            compound_exp_tree::CompoundExpNodeContainer lhs = exp_nodes[op_index];
            compound_exp_tree::CompoundExpNodeContainer rhs = exp_nodes[op_index + 1];
            syntax_tree::compound_expression::OperatorType operator_type = unprocessed_ops[op_index];

            // remove the left hand and right hand sides from exp_nodes
            exp_nodes.erase(exp_nodes.begin() + op_index);
            exp_nodes.erase(exp_nodes.begin() + op_index);

            unprocessed_ops.erase(unprocessed_ops.begin() + op_index);

            auto new_op_node = compound_exp_tree::CompoundExpOpNode(lhs, operator_type, rhs);
            compound_exp_tree::CompoundExpNodeContainer new_op_container(new_op_node);

            exp_nodes.insert(exp_nodes.begin() + op_index, new_op_container);

            // adjust op_current_positions_by_original_idx
            for (size_t i = 0; i < op_current_positions_by_original_idx.size(); i++)
            {
                size_t old_current_pos = op_current_positions_by_original_idx[i];

                if (old_current_pos >= op_index)
                {
                    // move left by one
                    op_current_positions_by_original_idx[i] -= 1;
                }
            }
        }

        // at this point, there are no unprocessed operations left
        // Try convert to value node, which contains instructions

        auto try_convert_to_value_node = convert_exp_node_to_value_node(exp_nodes[0]);
        if (std::holds_alternative<BytecodeCompilerError>(try_convert_to_value_node))
        {
            return std::get<BytecodeCompilerError>(try_convert_to_value_node);
        }

        compound_exp_tree::CompoundExpValueNode final_value_node =
            std::get<compound_exp_tree::CompoundExpValueNode>(try_convert_to_value_node);

        return final_value_node.instructions();
    }
}