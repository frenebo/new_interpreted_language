#include <iostream>

#include "./compound_expression.hpp"
#include "../terminal_expressions/terminal_expressions.hpp"

namespace syntax_tree_printer::compound_expression
{
    void print_compound_expression(const syntax_tree::compound_expression::CompoundExpression & compound_exp, unsigned int indents)
    {
        std::cout << std::string(indents, ' ') << "Compound Expression: \n";

        print_possibly_prefixed_terminal(compound_exp.start_exp(), indents + 1);

        for (auto suffix : compound_exp.suffixes())
        {
            // print operator
            if (suffix.op_type() == syntax_tree::compound_expression::OperatorType::MINUS_OP)
            {
                std::cout << std::string(indents + 1, ' ') << "Minus Operator\n";
            }
            else if (suffix.op_type() == syntax_tree::compound_expression::OperatorType::PLUS_OP)
            {
                std::cout << std::string(indents + 1, ' ') << "Plus Operator\n";
            }
            else if (suffix.op_type() == syntax_tree::compound_expression::OperatorType::MULT_OP)
            {
                std::cout << std::string(indents + 1, ' ') << "Multiplication Operator\n";
            }
            else if (suffix.op_type() == syntax_tree::compound_expression::OperatorType::DIV_OP)
            {
                std::cout << std::string(indents + 1, ' ') << "Division Operator\n";
            }
            else if (suffix.op_type() == syntax_tree::compound_expression::OperatorType::ASSIGNMENT_OP)
            {
                std::cout << std::string(indents + 1, ' ') << "Assignment Operator\n";
            }
            else
            {
                std::cout << std::string(indents + 1, ' ') << "Unimplemented operator print\n";
            }

            print_possibly_prefixed_terminal(suffix.terminal_exp(), indents + 2);
        }
    }
}