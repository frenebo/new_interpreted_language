#ifndef SYNTAX_TREE_TERMINAL_EXPRESSIONS_HPP
#define SYNTAX_TREE_TERMINAL_EXPRESSIONS_HPP

#include <variant>
#include <string>

namespace syntax_tree::terminal_expressions
{
    class IdentifierExpression
    {
    public:
        IdentifierExpression(std::string identifier_string);
        const std::string & identifier_string() const;
    private:
        std::string _identifier_string;
    };

    class NumberExpression
    {
    public:
        enum NumberType { FLOAT, INT };
        NumberExpression(std::string number_string, NumberType num_type);
        const std::string & number_string() const;
        NumberType number_type() const;
    private:
        std::string _number_string;
        NumberType _number_type;
    };

    class BoolLiteralExpression
    {
    public:
        BoolLiteralExpression(bool value);
        bool value() const;
    private:
        bool _value;
    };
    
    class TerminalExpressionContainer
    {
    public:
        typedef std::variant<
            IdentifierExpression,
            NumberExpression,
            BoolLiteralExpression
        > VariantTerminalExp;
        
        TerminalExpressionContainer(VariantTerminalExp contained_terminal_exp);
        const VariantTerminalExp & contained_terminal_exp() const;
    private:
        VariantTerminalExp _contained_terminal_exp;
    };
}

#endif
