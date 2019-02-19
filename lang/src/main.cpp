#include <iostream>
#include <variant>

#include "./code_processor/code_processor.hpp"
#include "./syntax_tree_printer/statement_series/statement_series.hpp"

int main()
{
	auto code_process_result = code_processor::parse_program(
		"a - b + c + -something + somethingelse;"
		"hello;"
	);
	if (std::holds_alternative<code_processor::CodeProcessorError>(code_process_result))
	{
		code_processor::CodeProcessorError code_process_err = std::get<code_processor::CodeProcessorError>(code_process_result);
		std::cout << "Code processing error: " << code_process_err.message() << "\n";
	}

	auto statement_series = std::get<syntax_tree::statement_series::StatementSeries>(code_process_result);
	
	syntax_tree_printer::statement_series::print_statement_series(statement_series, 0);
	
	return 0;
}
