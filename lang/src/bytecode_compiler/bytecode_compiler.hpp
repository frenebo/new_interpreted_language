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
        typedef std::vector<bytecode::instructions::InstructionContainer> InstructionsVec;
        typedef std::variant<InstructionsVec, BytecodeCompilerError> InstructionsOrErr;
        
        static void push_instructions(InstructionsVec & target_vec, const InstructionsVec & source_vec);
        
        BytecodeCompiler();
        
        InstructionsOrErr compile_statement_series(const syntax_tree::statement_series::StatementSeries & statement_series);
    private:
        InstructionsOrErr compile_statement_container(const syntax_tree::statements::StatementContainer & statement_container);
        InstructionsOrErr compile_compound_expression_statement(const syntax_tree::statements::CompoundExpressionStatement & compound_expression_statement);
        InstructionsOrErr compile_print_statement(const syntax_tree::statements::PrintStatement & print_statement);
        InstructionsOrErr compile_if_statement(const syntax_tree::statements::IfStatement & if_statement);
        InstructionsOrErr compile_for_statement(const syntax_tree::statements::ForLoopStatement & if_statement);
        InstructionsOrErr compile_compound_exp_evaluation(const syntax_tree::compound_expression::CompoundExpression & compound_exp);
        // InstructionsOrErr compile_possibly_prefixed_terminal_evaluation(const syntax_tree::compound_expression::PossiblyPrefixedTerminal & possibly_prefixed_terminal_expression);
        // InstructionsOrErr compile_terminal_evaluation(const syntax_tree::terminal_expressions::TerminalExpressionContainer & terminal_expression);

    };
}

#endif
