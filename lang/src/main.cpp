#include <iostream>

#include "./bytecode/instructions/instructions.hpp"
#include "./front_end/front_end.hpp"
#include "./syntax_tree_printer/statement_series/statement_series.hpp"
#include "./virtual_machine/runner.hpp"
#include "./bytecode_compiler/bytecode_compiler.hpp"
#include "./bytecode_printer/bytecode_printer.hpp"


void try_run_code(std::string input_text)
{
	auto try_parse = front_end::parse_program(input_text);

	if (std::holds_alternative<front_end::FrontEndError>(try_parse))
	{
		front_end::FrontEndError err = std::get<front_end::FrontEndError>(try_parse);
		std::cout << "Syntax Error: " << err.message() << "\n";
        return;
	}

	auto statement_series = std::get<syntax_tree::statement_series::StatementSeries>(try_parse);
	syntax_tree_printer::statement_series::print_statement_series(statement_series, 0);

	auto try_compile_instructions = bytecode_compiler::BytecodeCompiler().compile_statement_series(statement_series);
    if (std::holds_alternative<bytecode_compiler::BytecodeCompilerError>(try_compile_instructions))
    {
        bytecode_compiler::BytecodeCompilerError compiler_err = std::get<bytecode_compiler::BytecodeCompilerError>(try_compile_instructions);
        std::cout << "Compiler Error: " << compiler_err.message() << "\n";
        return;
    }

    std::vector<bytecode::instructions::InstructionContainer> instructions =
        std::get<std::vector<bytecode::instructions::InstructionContainer>>(try_compile_instructions);

    bytecode_printer::print_instructions(instructions);

	auto runtime_error_possible = virtual_machine::runner::run_bytecode(instructions);
    if (runtime_error_possible.has_value())
    {
        std::cout << "Runtime Error: " << runtime_error_possible->message() << "\n";
        return;
    }
}

#ifdef FOR_EMSCRIPTEN
extern "C" {
    int run_code_string(char* text)
    {
        try_run_code(std::string(text));
        return 0;
    }
}

int main() {
    return 0;
}

#else

#include <fstream>
// void

int main(int argc, char *argv[])
{
    // std::string input_text =
    //     "for (i = 0; i < 3; i += 1)"
    //     "{"
    //     "   print i;"
    //     "}";

	if (argc != 2)
    {
        std::cout << "Program takes one argument: input file name\n";
        return 1;
    }

    std::string file_name = std::string(argv[1]);

    std::ifstream input_file = std::ifstream(file_name);

    std::string input_text;
    if (input_file.is_open())
    {
        input_file.seekg(0, std::ios::end);
        input_text.reserve(input_file.tellg());
        input_file.seekg(0, std::ios::beg);

        input_text.assign(
            std::istreambuf_iterator<char>(input_file),
            std::istreambuf_iterator<char>()
        );
    }
    else
    {
        std::cout << "Could not open file \"" << file_name << "\"\n";
        return 1;
    }

    try_run_code(input_text);

	return 0;
}

#endif