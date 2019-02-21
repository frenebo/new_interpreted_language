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
        // syntax_tree::statements::
    };
}

#endif
