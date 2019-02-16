#include <iostream>
#include <variant>

#include "./codeprocessor/codeprocessor.hpp"

int main()
{
	auto code_process_result = codeprocessor::parse_program("something = 10.0;");
	if (std::holds_alternative<codeprocessor::CodeProcessorError>(code_process_result))
	{
		codeprocessor::CodeProcessorError code_process_err = std::get<codeprocessor::CodeProcessorError>(code_process_result);
		std::cout << "Code processing error: " << code_process_err.message() << "\n";
	}
	return 0;
}

