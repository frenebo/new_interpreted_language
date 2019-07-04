#include <iostream>

#include "./compound_expression.hpp"
#include "../terminal_expressions/terminal_expressions.hpp"

namespace syntax_tree_printer::compound_expression
{
    std::string op_name(syntax_tree::compound_expression::OperatorType op_type)
    {
        switch(op_type) {
        case syntax_tree::compound_expression::OperatorType::MINUS_OP:
            return "Minus Operator";
        case syntax_tree::compound_expression::OperatorType::PLUS_OP:
            return "Plus Operator";
        case syntax_tree::compound_expression::OperatorType::MULT_OP:
            return "Multiplication Operator";
        case syntax_tree::compound_expression::OperatorType::DIV_OP:
            return "Division Operator";
        case syntax_tree::compound_expression::OperatorType::ASSIGNMENT_OP:
            return "Assignment Operator";
        case syntax_tree::compound_expression::OperatorType::MINUS_EQUALS_ASSIGNMENT_OP:
            return "Minus Equals Assignment Operator";
        case syntax_tree::compound_expression::OperatorType::PLUS_EQUALS_ASSIGNMENT_OP:
            return "Plus Equals Assignment Operator";
        case syntax_tree::compound_expression::OperatorType::MODULO_OP:
            return "Modulo Operator";
        case syntax_tree::compound_expression::OperatorType::AND_OP:
            return "And Operator";
        case syntax_tree::compound_expression::OperatorType::OR_OP:
            return "Or Operator";
        case syntax_tree::compound_expression::OperatorType::EQUALITY_COMPARISON_OP:
            return "Equality Comparison Operator";
        case syntax_tree::compound_expression::OperatorType::NOT_EQUALS_COMPARISON_OP:
            return "Not Equals Operator";
        case syntax_tree::compound_expression::OperatorType::MORE_THAN_OP:
            return "More Than Operator";
        case syntax_tree::compound_expression::OperatorType::LESS_THAN_OP:
            return "Less Than Operator";
        case syntax_tree::compound_expression::OperatorType::MORE_THAN_OR_EQUAL_OP:
            return "More Than Or Equal Operator";
        case syntax_tree::compound_expression::OperatorType::LESS_THAN_OR_EQUAL_OP:
            return "Less Than Or Equal Operator";
        default:
            return "Unimplemented operator print";
        }
    }

    void print_compound_expression(const syntax_tree::compound_expression::CompoundExpression & compound_exp, unsigned int indents)
    {
        std::cout << std::string(indents, ' ') << "Compound Expression: \n";

        print_possibly_prefixed_terminal(compound_exp.start_exp(), indents + 1);

        for (auto suffix : compound_exp.suffixes())
        {
            std::cout << std::string(indents + 1, ' ') << op_name(suffix.op_type()) << "\n";
            print_possibly_prefixed_terminal(suffix.terminal_exp(), indents + 2);
        }
    }
}