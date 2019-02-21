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
    }

    int op_type_priority(syntax_tree::compound_expression::OperatorType op_type)
    {
        switch (op_type)
        {
            case syntax_tree::compound_expression::OperatorType::MINUS_OP:
            case syntax_tree::compound_expression::OperatorType::PLUS_OP:
                return 0;
        }
    }

    bool index_op_type_pair_sort(
        std::pair<unsigned int, syntax_tree::compound_expression::OperatorType> i,
        std::pair<unsigned int, syntax_tree::compound_expression::OperatorType> j)
    {
        int i_priority = op_type_priority(i.second);
        int j_priority = op_type_priority(j.second);

        // i stays before j if it is equivalent, or if it has a higher priority
        return i >= j;
    }

    std::vector<bytecode::instructions::InstructionContainer>
    BytecodeCompiler::instructions_to_evaluate_compound_exp_to_stack(const syntax_tree::compound_expression::CompoundExpression & compound_exp)
    {
        std::vector<const syntax_tree::compound_expression::PossiblyPrefixedTerminal &> possibly_prefixed_terminals;
        std::vector<syntax_tree::compound_expression::OperatorType> op_types;
        
        possibly_prefixed_terminals.push_back(compound_exp.start_exp());

        for (const syntax_tree::compound_expression::CompoundExpressionSuffix & suffix : compound_exp.suffixes())
        {
            possibly_prefixed_terminals.push_back(suffix.terminal_exp());

            op_types.push_back(suffix.op_type());
        }

        std::vector<std::pair<unsigned int, syntax_tree::compound_expression::OperatorType>> sorted_op_types_with_indices;
        for (unsigned int i = 0; i < op_types.size(); ++i)
        {
            sorted_op_types_with_indices.push_back(
                std::pair<unsigned int, syntax_tree::compound_expression::OperatorType>(i, op_types[i])
            );
        }

        // this orders the operators, highest priority first and lowest priority last. Each item
        // contains the original index of the operator in the expression.
        // So, the expression a + b * c would have the give these sorted op types with indices:
        // [
        // 1, multiplication
        // 0, addition 
        // ]
        std::stable_sort(sorted_op_types_with_indices.begin(), sorted_op_types_with_indices.end(), index_op_type_pair_sort);

        // std::vector<bytecode::instructions::InstructionContainer> 

        std::vector<bytecode::instructions::InstructionContainer> instructions;
        
        // push first terminal to stack
        std::vector<bytecode::instructions::InstructionContainer> first_terminal_instructions =
            instructions_to_evaluate_possibly_prefixed_terminal_to_stack(possibly_prefixed_terminals[0]);
        
        instructions.insert(instructions.end(), first_terminal_instructions.begin(), first_terminal_instructions.end());

        /**
         * NOTE ABOUT THE EVALUATION OF COMPOUND EXPRESSIONS
         * 
         * in this expression: 1 + 5*9, it's necessary to execute the multiplication operation
         * before the addition operation.
         * This is what the compiled code does:
         * When 1 is on the stack and it is time to push 5 to the stack,
         * the addition operation needs to wait for the multiplication operation (5*9)
         * to finish executing. So, the operations would be,
         * 1 Load 1 to stack
         * # stack: 1
         * 2 Load 5 to stack
         * # stack: 1, 5
         * 3 Load 9 to stack
         * # stack: 1, 5, 9
         * 4 multiply stack
         * # stack: 1, 45
         * 5 add stack
         * # stack: 46
         * The way it is decided whether an operation needs to be postponed until another
         * operation has been completed (in this case, the addition is postponed
         * until the multiplication has taken place) is whether the current
         * operation has more priority than the next operation. The priorities
         * is determined by order of operations (exponents, multiplication/division, addition/subraction),
         * and if there is two operations are equivalent in the order of operations, the left one
         * has higher priority. So, in the expression
         * a + b + c * d * e + f * g,
         * the priorities are:
         * a + b + c * d * e + f * g,
         *   2   1   5   4   0   3
         * With higher numbers under the operations indicating higher priority.
         * 
         * Things start with a loaded to the stack.
         * 
         * B is loaded to the stack. The postponed operations stack is empty, so it is left alone.
         * The priority of the operation before b (2) is higher than the priority of the
         * operation before c (1). B operation has a priority higher
         * than c operation,  so the addition operation occurs.
         * 
         * C is loaded to the stack. The postponed operations stack is empty, so it is left alone.
         * The priority of the operaiton before c (1) is lower than the priority of the
         * operation before d (5). C operation has a priority LOWER
         * than d operation, so the addition operation is postponed, pushed onto the postponed
         * operation list.
         * 
         * D is loaded onto the stack. The postponed operations stack has at the end an
         * operation with the priority 1, which is lower than the priority of the operation
         * before d (5), so the stack is left alone.
         * The priority of the operation before d (5) is higher than the priority of the
         * operation before e (4). D operation has a priority higher
         * than e operation, so the multiplication operation occurs.
         * 
         * E is loaded onto the stack. The postponed operations stack has at the end an
         * operation with the priority 1, which is lower than the priority of the operation
         * before e (4), so the stack is left alone.
         * The priority of the operation before e (4) is higher than the priority of the
         * operation before f (0). E operation has a priority higher
         * than f operation, so the multiplication operation occurs.
         * 
         * F is loaded onto the stack. The postponed operations stack has at the end an
         * operation with the priority 1, which is HIGHER than the priority of the operation before f (0),
         * so the last item on the postponed operations stack is removed and executed.
         * This check is performed again - but the stack is empty, so it is left alone. However,
         * if there were still operations on the postponed stack, those operations would be
         * removed and continued as long as they had priorities higher than the priority of the
         * operation before f (0).
         * The priority of the operation before f (0) is lower than the priority of the
         * operation before g (3). F operation has a priority lower
         * than g operation, so the operation is postponed, pushed onto the postponed operation list.
         * 
         * G is loaded onto the stack. The postponed operations stack has at the end an
         * operation with priority 0, which is lower then the priority of the operation before g (3),
         * so the stack is left alone.
         * There is no operation after g's operation, so the operation before g occurs.
         * 
         * There are no more terminals (a, b, c, d, f, g), so operations are removed from the end
         * of the postponed stack and executed until the postponed stack is empty.
         * 
         * What is left is the evaluated result of a compound expression using order of operations.
         */


        
        for (int instruction_idx = 0; instruction_idx < op_types.size(); instruction_idx++)
        {
            // push this terminal to stack
            std::vector<bytecode::instructions::InstructionContainer> evaluate_terminal_instructions =
                instructions_to_evaluate_possibly_prefixed_terminal_to_stack(possibly_prefixed_terminals[instruction_idx + 1]);
            
            instructions.insert(instructions.end(), evaluate_terminal_instructions.begin(), evaluate_terminal_instructions.end());
        }
    }

    std::vector<bytecode::instructions::InstructionContainer>
    BytecodeCompiler::instructions_to_evaluate_possibly_prefixed_terminal_to_stack(const syntax_tree::compound_expression::PossiblyPrefixedTerminal & possibly_prefixed_terminal_expression)
    {
        auto instructions = instructions_to_evaluate_terminal_to_stack(possibly_prefixed_terminal_expression.terminal_exp_container());

        auto possible_prefix_type = possibly_prefixed_terminal_expression.possible_prefix_type();
        if (possible_prefix_type.has_value())
        {
            if (*possible_prefix_type == syntax_tree::compound_expression::PrefixType::MINUS_PREFIX)
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