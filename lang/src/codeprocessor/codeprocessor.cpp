#include <iostream>
#include <variant>

#include "./codeprocessor.hpp"
#include "./lexer/lexer.hpp"
#include "./parser/statementseries/statementseries.hpp"

namespace codeprocessor
{
    std::variant<syntaxtree::statement_series::StatementSeries, CodeProcessorError>
    parse_program(const std::string & text)
    {
        auto lex_result = lexer::Lexer().lex_text(text);

        // if there was a problem lexing
        if (std::holds_alternative<lexer::LexErrorMessage>(lex_result))
        {
            lexer::LexErrorMessage lex_error_mssg = std::get<lexer::LexErrorMessage>(lex_result);
            
            return CodeProcessorError(lex_error_mssg.reason());
        }

        std::vector<tokens::Token> tokens = std::get<std::vector<tokens::Token>>(lex_result);

        auto parse_result = parser::statement_series::parse_statement_series(tokens, 0, tokens::TokenType::END_OF_INPUT);

        if (std::holds_alternative<parser::ParseError>(parse_result))
        {
            parser::ParseError parse_err = std::get<parser::ParseError>(parse_result);
            return CodeProcessorError(parse_err.message());
        }
        else
        {
            return std::get<syntaxtree::statement_series::StatementSeries>(parse_result);
        }
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