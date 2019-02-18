#include <iostream>

#include "./terminal_expressions.hpp"

namespace syntax_tree_printer::terminal_expressions
{
    void print_number_expression(const syntax_tree::terminal_expressions::NumberExpression & number_exp, unsigned int indents)
    {
        std::string num_type_str = "Unimplemented number type";
        if (number_exp.number_type() == syntax_tree::terminal_expressions::NumberExpression::NumberType::FLOAT)
        {
            num_type_str = "Float";
        }
        else if (number_exp.number_type() == syntax_tree::terminal_expressions::NumberExpression::NumberType::INT)
        {
            num_type_str = "Integer";
        }

        std::cout << std::string(indents, ' ') << num_type_str + number_exp.number_string() + "\n";
    }
}
