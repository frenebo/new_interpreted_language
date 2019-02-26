#ifndef BYTECODE_COMPILER_HPP
#define BYTECODE_COMPILER_HPP

#include <string>
#include <vector>
#include <variant>

#include "../bytecode/instructions/instructions.hpp"
#include "../syntax_tree/statement_series/statement_series.hpp"

namespace bytecode_compiler
{
    class BytecodeCompilerError
    {
    public:
        BytecodeCompilerError(std::string message);
        const std::string & message() const;
    private:
        std::string _message;
    };
    
    class BytecodeCompiler
    {
    public:
        BytecodeCompiler();

        typedef std::vector<bytecode::instructions::InstructionContainer> InstructionsVec;
        typedef std::variant<InstructionsVec, BytecodeCompilerError> InstructionsOrErr;
        
        InstructionsOrErr compile_statement_series(const syntax_tree::statement_series::StatementSeries & statement_series);
    private:
        InstructionsOrErr compile_statement_container(const syntax_tree::statements::StatementContainer & statement_container);
        InstructionsOrErr compile_compound_expression_statement(const syntax_tree::statements::CompoundExpressionStatement & compound_expression_statement);
        InstructionsOrErr compile_print_statement(const syntax_tree::statements::PrintStatement & print_statement);
        InstructionsOrErr compile_if_statement(const syntax_tree::statements::IfStatement & if_statement);
        InstructionsOrErr instructions_to_evaluate_compound_exp_to_stack(const syntax_tree::compound_expression::CompoundExpression & compound_exp);
        InstructionsOrErr instructions_to_evaluate_possibly_prefixed_terminal_to_stack(const syntax_tree::compound_expression::PossiblyPrefixedTerminal & possibly_prefixed_terminal_expression);
        InstructionsOrErr instructions_to_evaluate_terminal_to_stack(const syntax_tree::terminal_expressions::TerminalExpressionContainer & terminal_expression);
        InstructionsOrErr instruction_to_evaluate_number_expression_to_stack(const syntax_tree::terminal_expressions::NumberExpression & number_expression);
        InstructionsOrErr instruction_to_evaluate_identifier_to_stack(const syntax_tree::terminal_expressions::IdentifierExpression & identifier_expression);
        InstructionsOrErr instructions_for_stack_operation(syntax_tree::compound_expression::OperatorType op_type);

        static void push_instructions(InstructionsVec & target_vec, const InstructionsVec & source_vec);
    };
}

#endif
