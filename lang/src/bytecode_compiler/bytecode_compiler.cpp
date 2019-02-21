#include <iostream>
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
    compile_compound_expression_statement(const syntax_tree::statements::CompoundExpressionStatement & compound_expression_statement)
    {
        std::cout << "Unimplemented compound expression statement\n";
    }

    std::vector<bytecode::instructions::InstructionContainer>
    compile_print_statement(const syntax_tree::statements::PrintStatement & print_statement)
    {
        std::cout << "Unimplemented print statement\n";
    }
}