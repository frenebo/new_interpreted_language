#include <iostream>
#include <variant>

#include "./codeprocessor.hpp"
#include "./lexer/lexer.hpp"

namespace codeprocessor
{
    std::variant<syntaxtree::statementseries::StatementSeries, CodeProcessorError>
    parse_program(const std::string & text)
    {
        auto lex_result = lexer::lex_text(text);

        // if there was a problem lexing
        if (std::holds_alternative<lexer::LexErrorMessage>(lex_result))
        {
            lexer::LexErrorMessage lex_error_mssg = std::get<lexer::LexErrorMessage>(lex_result);
            
            return CodeProcessorError(lex_error_mssg.reason());
        }

        std::vector<tokens::Token> tokens = std::get<std::vector<tokens::Token>>(lex_result);
    }
    
    void helloworld()
    {
        std::cout << "Hello, World!\n";
    }

    CodeProcessorError::CodeProcessorError(std::string message)
    : _message(message)
    {
    }

    const std::string & CodeProcessorError::message() const
    {
        return _message;
    }
}