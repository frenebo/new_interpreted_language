#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include <variant>

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
    
    std::variant<std::vector<tokens::Token>, LexErrorMessage> lex_text(const std::string & text);
}

#endif
