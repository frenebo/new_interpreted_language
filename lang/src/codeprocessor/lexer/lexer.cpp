#include "./lexer.hpp"

#include <optional>
#include <variant>

namespace lexer
{
    std::variant<tokens::Token, LexErrorMessage> try_match_tok(const std::string & text, unsigned long start_idx)
    {
        return LexErrorMessage("unimplemented");
    }

    // lexes text, including whitespace. Does not add End Of Input token to the end.
    std::variant<std::vector<tokens::Token>, LexErrorMessage> lex_simple(const std::string & text)
    {
        std::vector<tokens::Token> tokens;

        unsigned long consumed_chars = 0;

        while (consumed_chars < text.length())
        {
            auto try_match = try_match_tok(text, consumed_chars);

            // if there was a problem and try_match_tok returned an error
            if (std::holds_alternative<LexErrorMessage>(try_match))
            {
                LexErrorMessage lex_error_mssg = std::get<LexErrorMessage>(try_match);
                return lex_error_mssg;
            }
            // otherwise, add result token to tokens, increase consumed_chars, and continue
            else
            {
                tokens::Token match_tok = std::get<tokens::Token>(try_match);
                tokens.push_back(match_tok);
                consumed_chars += match_tok.content_text().length();
            }
        }

        return tokens;
    }
    
    std::variant<std::vector<tokens::Token>, LexErrorMessage> lex_text(const std::string & text)
    {
        auto simple_lex_result = lex_simple(text);

        // if simple lex was unable to lex the text, and returned an error message
        if (std::holds_alternative<LexErrorMessage>(simple_lex_result))
        {
            LexErrorMessage lex_error_mssg = std::get<LexErrorMessage>(simple_lex_result);
            return lex_error_mssg;
        }
        
        // otherwise, get the result tokens of the simple lexer
        std::vector<tokens::Token> including_whitespace = std::get<std::vector<tokens::Token>>(simple_lex_result);

        std::vector<tokens::Token> result;

        // filter including_whitespace to skip whitespace
        for (auto tok : including_whitespace)
        {
            if (tok.token_type() != tokens::TokenType::WHITESPACE)
            {
                result.push_back(tok);
            }
        }

        // Add an End Of Input token to the end
        result.push_back(tokens::Token(tokens::TokenType::END_OF_INPUT, ""));

        return result;
    }

    LexErrorMessage::LexErrorMessage(std::string reason)
    : _reason(reason)
    {
    }

    const std::string & LexErrorMessage::reason() const
    {
        return _reason;
    }
}