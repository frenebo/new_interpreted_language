#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include <variant>
#include <optional>
#include <map>

#include "../tokens/tokens.hpp"

namespace lexer
{
    class LexErrorMessage
    {
        std::string _reason;
    public:
        LexErrorMessage(std::string reason);
        const std::string & reason() const;
    };

    class Lexer
    {
        std::map<std::string, tokens::TokenType> _simple_tok_strings;

        std::variant<std::vector<tokens::Token>, LexErrorMessage> lex_simple(const std::string & text) const;
        std::variant<tokens::Token, LexErrorMessage> try_match_tok(const std::string & text, unsigned long start_idx) const;
        std::optional<tokens::Token> longest_simple_tok_match(const std::string & text, unsigned long start_idx) const;
        std::optional<tokens::Token> try_match_identifier(const std::string & text, unsigned long start_idx) const;
        std::optional<tokens::Token> try_match_whitespace(const std::string & text, unsigned long start_idx) const;
        std::optional<tokens::Token> try_match_int_or_float(const std::string & text, unsigned long start_idx) const;
    public:
        // @TODO add lexer options?
        Lexer();
        std::variant<std::vector<tokens::Token>, LexErrorMessage> lex_text(const std::string & text) const;
    };
}

#endif
