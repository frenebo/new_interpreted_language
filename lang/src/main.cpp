#include <iostream>

#include "./bytecode/instructions/instructions.hpp"
#include "./front_end/front_end.hpp"
#include "./syntax_tree_printer/statement_series/statement_series.hpp"
#include "./virtual_machine/runner.hpp"
#include "./bytecode_compiler/bytecode_compiler.hpp"
#include "./bytecode_printer/bytecode_printer.hpp"


int main()
{
	virtual_machine::machine_state::MachineState state = virtual_machine::machine_state::MachineState();

	while (true)
	{
		std::cout << "> ";
		std::string input_line;
		std::getline(std::cin, input_line);
		auto try_parse = front_end::parse_program(input_line);

		if (std::holds_alternative<front_end::FrontEndError>(try_parse))
		{
			front_end::FrontEndError err = std::get<front_end::FrontEndError>(try_parse);
			std::cout << "Syntax error: " << err.message() << "\n";
			continue;
		}

		auto statement_series = std::get<syntax_tree::statement_series::StatementSeries>(try_parse);
		syntax_tree_printer::statement_series::print_statement_series(statement_series, 0);
		
		auto instructions = bytecode_compiler::BytecodeCompiler().compile_statement_series(statement_series);

		bytecode_printer::print_instructions(instructions);
		state.replace_instructions(instructions);

		while (!state.machine_done())
		{
			std::optional<virtual_machine::machine_state::MachineRuntimeError> problem =
				state.execute_next_instruction();
			
			if (problem.has_value())
			{
				std::cout << "Runtime error: " << problem->message() << "\n";
				break;
			}
		}
	}

	return 0;
}
