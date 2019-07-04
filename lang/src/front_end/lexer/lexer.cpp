#include "./lexer.hpp"
#include <ctype.h>
#include <optional>
#include <variant>

namespace lexer
{
    Lexer::Lexer()
    {
        _simple_tok_strings = {
            { "=",     tokens::TokenType::EQUALS_SIGN },
            { "+=",    tokens::TokenType::PLUS_EQUALS },
            { "-=",    tokens::TokenType::MINUS_EQUALS },
            { "-",     tokens::TokenType::MINUS_SIGN },
            { "+",     tokens::TokenType::PLUS_SIGN },
            { "*",     tokens::TokenType::ASTERISK },
            { "/",     tokens::TokenType::FORWARD_SLASH },
            { "%",     tokens::TokenType::PERCENT_SIGN },
            { ";",     tokens::TokenType::SEMICOLON },
            { "(",     tokens::TokenType::OPEN_PARENTHESIS },
            { ")",     tokens::TokenType::CLOSE_PARENTHESIS },
            { "{",     tokens::TokenType::OPEN_BRACE },
            { "}",     tokens::TokenType::CLOSE_BRACE },
            { "<",     tokens::TokenType::LESS_THAN_OP },
            { "<=",    tokens::TokenType::LESS_THAN_OR_EQUAL_OP },
            { ">",     tokens::TokenType::MORE_THAN_OP },
            { ">=",    tokens::TokenType::MORE_THAN_OR_EQUAL_OP },
            { "==",    tokens::TokenType::DOUBLE_EQUALS },
            { "||",    tokens::TokenType::DOUBLE_VERTICAL_BAR },
            { "&&",    tokens::TokenType::DOUBLE_AMPERSAND },
            { "print", tokens::TokenType::PRINT_KEYWORD },
            { "if",    tokens::TokenType::IF_KEYWORD },
            { "else",  tokens::TokenType::ELSE_KEYWORD },
            { "for",   tokens::TokenType::FOR_KEYWORD },
            { "true",  tokens::TokenType::TRUE_KEYWORD },
            { "false", tokens::TokenType::FALSE_KEYWORD },
        };
    }

    std::variant<std::vector<tokens::Token>, LexErrorMessage> Lexer::lex_text(const std::string & text) const
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
        result.push_back(tokens::Token(tokens::TokenType::END_OF_INPUT, text.size(), ""));

        return result;
    }

    // lexes text, including whitespace. Does not add End Of Input token to the end.
    std::variant<std::vector<tokens::Token>, LexErrorMessage> Lexer::lex_simple(const std::string & text) const
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

    std::optional<tokens::Token> Lexer::try_match_string_literal(const std::string & text, const unsigned long start_idx) const
    {
        unsigned long consumed_count = 0;
        if (text[start_idx + consumed_count] != '"')
        {
            return std::optional<tokens::Token>();
        }
        else
        {
            consumed_count++;
        }

        bool is_terminated = false;

        while (consumed_count < text.length() - start_idx)
        {
            char next_char = text[start_idx + consumed_count];
            consumed_count++;

            if (next_char == '"')
            {
                is_terminated = true;
                break;
            }
        }

        std::string matched_str = text.substr(start_idx, consumed_count);

        if (is_terminated)
        {
            return tokens::Token(tokens::TokenType::STRING_LITERAL, start_idx, matched_str);
        }
        else
        {
            return std::optional<tokens::Token>();
        }
    }

    std::variant<tokens::Token, LexErrorMessage> Lexer::try_match_tok(const std::string & text, const unsigned long start_idx) const
    {
        std::optional<tokens::Token> longest_match;

        std::vector<std::optional<tokens::Token>> potential_matches;
        potential_matches.push_back(longest_simple_tok_match(text, start_idx));
        potential_matches.push_back(try_match_identifier(text, start_idx));
        potential_matches.push_back(try_match_whitespace(text, start_idx));
        potential_matches.push_back(try_match_int_or_float(text, start_idx));
        potential_matches.push_back(try_match_string_literal(text, start_idx));

        for (std::optional<tokens::Token> potential_match : potential_matches)
        {
            // if the potential match has a value, and it's either longer than the old longest match or it's the first match
            if (potential_match.has_value() &&
                (
                    !longest_match.has_value() ||
                    potential_match->content_text().length() > longest_match->content_text().length()
                ))
            {
                longest_match = potential_match;
            }
        }

        if (longest_match.has_value())
        {
            return *longest_match;
        }
        else
        {
            return LexErrorMessage("Could not lex text");
        }
    }

    std::optional<tokens::Token> Lexer::try_match_int_or_float(const std::string & text, const unsigned long start_idx) const
    {
        bool seen_period = false;
        unsigned long digits_before_period = 0;
        unsigned long digits_after_period = 0;

        unsigned long consumed_count = 0;
        while (consumed_count < text.length() - start_idx)
        {
            char next_char = text[start_idx + consumed_count];

            if (next_char == '.')
            {
                // only one period can be in a number
                if (seen_period) break;
                else
                {
                    consumed_count++;
                    seen_period = true;
                }
            }
            else if (isdigit(next_char))
            {
                consumed_count++;

                if (seen_period) digits_after_period++;
                else             digits_before_period++;
            }
            // the number is over if the next char is neither a period nor a digit
            else
            {
                break;
            }
        }

        // if no digits were seen
        if (digits_before_period == 0 && digits_after_period == 0)
        {
            return std::optional<tokens::Token>();
        }

        std::string matched_str = text.substr(start_idx, consumed_count);

        // if there was a period somewhere, this is a float
        if (seen_period)
        {
            return tokens::Token(tokens::TokenType::FLOAT_NUM, start_idx, matched_str);
        }
        // if there was no period, this is an int
        else
        {
            return tokens::Token(tokens::TokenType::INTEGER_NUM, start_idx, matched_str);
        }
    }

    std::optional<tokens::Token> Lexer::try_match_identifier(const std::string & text, const unsigned long start_idx) const
    {
        // the first character of an identifier must be a letter
        if (!isalpha(text[start_idx]) && text[start_idx] != '_') return std::optional<tokens::Token>();

        // one for the first character that has been verified to be a letter
        unsigned long match_length = 1;

        while (
            match_length < text.length() - start_idx &&
            (isalnum(text[start_idx + match_length]) || text[start_idx + match_length] == '_')
        ) {
            match_length++;
        }

        std::string matched_str = text.substr(start_idx, match_length);

        return tokens::Token(tokens::TokenType::IDENTIFIER, start_idx, matched_str);
    }

    std::optional<tokens::Token> Lexer::try_match_whitespace(const std::string & text, const unsigned long start_idx) const
    {
        unsigned long match_length = 0;

        while (
            match_length < text.length() - start_idx &&
            isspace(text[start_idx + match_length])
        ) {
            match_length++;
        }

        if (match_length == 0)
        {
            return std::optional<tokens::Token>();
        }
        else
        {
            std::string matched_str = text.substr(start_idx, match_length);

            return tokens::Token(tokens::TokenType::WHITESPACE, start_idx, matched_str);
        }
    }

    std::optional<tokens::Token> Lexer::longest_simple_tok_match(const std::string & text, const unsigned long start_idx) const
    {
        std::optional<tokens::Token> longest_match;

        for (const std::pair<std::string, tokens::TokenType>& pair : _simple_tok_strings)
        {
            const std::string & match_tok_string = pair.first;

            // if there has been a previous match and that match is longer than this one could be,
            // there's no point in testing this one
            if (longest_match.has_value() &&
                longest_match->content_text().length() > match_tok_string.length())
            {
                continue;
            }

            int text_compare = text.compare(start_idx, match_tok_string.length(), match_tok_string);

            // if the comparison doesn't return 0 for exact match
            if (text_compare != 0)
            {
                continue;
            }

            longest_match = tokens::Token(pair.second, start_idx, pair.first);
        }

        return longest_match;
    }
}