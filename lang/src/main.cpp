#include <iostream>
#include <variant>
#include <ctime>

#include "./bytecode/instructions/instructions.hpp"
#include "./front_end/front_end.hpp"
#include "./syntax_tree_printer/statement_series/statement_series.hpp"
#include "./virtual_machine/runner.hpp"

int main()
{
	auto code_process_result = front_end::parse_program(
		"a - b + c + c - something + somethingelse;"
		"print a;"
	);

	if (std::holds_alternative<front_end::FrontEndError>(code_process_result))
	{
		front_end::FrontEndError code_process_err = std::get<front_end::FrontEndError>(code_process_result);
		std::cout << "Code processing error: " << code_process_err.message() << "\n";
		return 1;
	}

	auto statement_series = std::get<syntax_tree::statement_series::StatementSeries>(code_process_result);

	syntax_tree_printer::statement_series::print_statement_series(statement_series, 0);

	std::vector<bytecode::instructions::InstructionContainer> instructions;

	instructions.push_back(bytecode::instructions::InstructionContainer(
		0,
		bytecode::instructions::StackIntegerPushConst(1)
	));
	for (int i = 0; i < 1000; i++)
	{
		instructions.push_back(bytecode::instructions::InstructionContainer(
			0,
			bytecode::instructions::StackIntegerPushConst(100)
		));
		instructions.push_back(bytecode::instructions::InstructionContainer(
			2,
			bytecode::instructions::StackAdd()
		));
		instructions.push_back(bytecode::instructions::InstructionContainer(
			1,
			bytecode::instructions::StackIntegerPushConst(99)
		));
		instructions.push_back(bytecode::instructions::InstructionContainer(
			2,
			bytecode::instructions::StackSubtract()
		));
	}
	instructions.push_back(bytecode::instructions::InstructionContainer(
		3,
		bytecode::instructions::StackPrint()
	));

	std::clock_t start;
    double duration;
	start = std::clock();

	auto machine_result = virtual_machine::runner::run_bytecode(instructions);
	if (machine_result.has_value())
	{
		std::cout << machine_result->message();
	}

	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout<< "Duration: "<< duration <<'\n';

	return 0;
}
