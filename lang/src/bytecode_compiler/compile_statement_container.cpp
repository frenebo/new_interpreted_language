#include "./bytecode_compiler.hpp"

namespace bytecode_compiler
{
    BytecodeCompiler::InstructionsOrErr BytecodeCompiler::compile_statement_container(const syntax_tree::statements::StatementContainer & statement_container)
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
        else if (std::holds_alternative<syntax_tree::statements::ForLoopStatement>(contained_statement))
        {
            return compile_for_statement(std::get<syntax_tree::statements::ForLoopStatement>(contained_statement));
        }
        else
        {
            return BytecodeCompilerError("Unimplemented statement compile\n");
        }
    }

}