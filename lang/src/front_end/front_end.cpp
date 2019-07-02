#include <iostream>
#include <variant>

#include "./front_end.hpp"
#include "./lexer/lexer.hpp"
#include "./parser/statement_series/statement_series.hpp"

namespace front_end
{
    std::variant<syntax_tree::statement_series::StatementSeries, FrontEndError>
    parse_program(const std::string & text)
    {
        std::cout << "Input text: " << text << "\n";
        auto lex_result = lexer::Lexer().lex_text(text);

        // if there was a problem lexing
        if (std::holds_alternative<lexer::LexErrorMessage>(lex_result))
        {
            lexer::LexErrorMessage lex_error_mssg = std::get<lexer::LexErrorMessage>(lex_result);

            return FrontEndError(lex_error_mssg.reason());
        }

        std::vector<tokens::Token> tokens = std::get<std::vector<tokens::Token>>(lex_result);

        std::cout << tokens.size() << " tokens: " << "\n";
        for (const tokens::Token & tok : tokens)
        {
            std::cout << "  " << tokens::tok_type_to_str(tok.token_type()) << "\n";
        }
        // tokens::

        auto parse_result = parser::statement_series::parse_statement_series(tokens, 0, tokens::TokenType::END_OF_INPUT);

        if (std::holds_alternative<parser::ParseError>(parse_result))
        {
            parser::ParseError parse_err = std::get<parser::ParseError>(parse_result);
            return FrontEndError(parse_err.message());
        }
        else
        {
            return std::get<parser::ParseResult<syntax_tree::statement_series::StatementSeries>>(parse_result).contained();
        }
    }

    FrontEndError::FrontEndError(std::string message)
    : _message(message)
    {
    }

    const std::string & FrontEndError::message() const
    {
        return _message;
    }
}