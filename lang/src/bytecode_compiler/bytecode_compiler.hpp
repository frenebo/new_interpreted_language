#ifndef BYTECODE_COMPILER_HPP
#define BYTECODE_COMPILER_HPP

#include "../bytecode/instructions/instructions.hpp"
#include "../syntax_tree/statement_series/statement_series.hpp"

namespace bytecode_compiler
{
    class BytecodeCompiler
    {
    public:
        BytecodeCompiler();
        
        std::vector<bytecode::instructions::InstructionContainer>
        compile_program(const syntax_tree::statement_series::StatementSeries & statement_series);
    private:
        std::vector<bytecode::instructions::InstructionContainer>
        compile_statement_container(const syntax_tree::statements::StatementContainer & statement_container);

        std::vector<bytecode::instructions::InstructionContainer>
        compile_compound_expression_statement(const syntax_tree::statements::CompoundExpressionStatement & compound_expression_statement);
        
        std::vector<bytecode::instructions::InstructionContainer>
        compile_print_statement(const syntax_tree::statements::PrintStatement & print_statement);

        std::vector<bytecode::instructions::InstructionContainer>
        compile_assignment_statement(const syntax_tree::statements::AssignmentStatement & assignment_statement);

        std::vector<bytecode::instructions::InstructionContainer>
        instructions_to_evaluate_compound_exp_to_stack(const syntax_tree::compound_expression::CompoundExpression & compound_exp);

        std::vector<bytecode::instructions::InstructionContainer>
        instructions_to_evaluate_possibly_prefixed_terminal_to_stack(const syntax_tree::compound_expression::PossiblyPrefixedTerminal & possibly_prefixed_terminal_expression);

        std::vector<bytecode::instructions::InstructionContainer>
        instructions_to_evaluate_terminal_to_stack(const syntax_tree::terminal_expressions::TerminalExpressionContainer & terminal_expression);

        std::vector<bytecode::instructions::InstructionContainer>
        instruction_to_evaluate_number_expression_to_stack(const syntax_tree::terminal_expressions::NumberExpression & number_expression);

        std::vector<bytecode::instructions::InstructionContainer>
        instruction_to_evaluate_identifier_to_stack(const syntax_tree::terminal_expressions::IdentifierExpression & identifier_expression);

        bytecode::instructions::InstructionContainer
        instruction_for_stack_operation(syntax_tree::compound_expression::OperatorType op_type);
    };
}

#endif
