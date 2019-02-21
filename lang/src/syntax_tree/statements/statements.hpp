#ifndef SYNTAX_TREE_STATEMENTS_HPP
#define SYNTAX_TREE_STATEMENTS_HPP

#include "../compound_expression/compound_expression.hpp"
#include <variant>

namespace syntax_tree::statements
{
    class PrintStatement
    {
    public:
        PrintStatement(syntax_tree::compound_expression::CompoundExpression exp_to_print);
        const syntax_tree::compound_expression::CompoundExpression & exp_to_print() const;
    private:
        syntax_tree::compound_expression::CompoundExpression _exp_to_print;
    };

    class AssignmentStatement
    {
    public:
        AssignmentStatement(std::string var_name, syntax_tree::compound_expression::CompoundExpression assigned_exp);
        const std::string & var_name() const;
        const syntax_tree::compound_expression::CompoundExpression & assigned_exp() const;
    private:
        std::string _var_name;
        syntax_tree::compound_expression::CompoundExpression _assigned_exp;
    };
    
    class CompoundExpressionStatement
    {
    public:
        CompoundExpressionStatement(syntax_tree::compound_expression::CompoundExpression compound_exp);
        const syntax_tree::compound_expression::CompoundExpression & compound_exp() const;
    private:
        syntax_tree::compound_expression::CompoundExpression _compound_exp;
    };
    
    class StatementContainer
    {
    public:
        typedef std::variant<
            CompoundExpressionStatement,
            PrintStatement,
            AssignmentStatement
        > VariantContainedStatement;
        
        StatementContainer(VariantContainedStatement contained_statement);
        
        const VariantContainedStatement & contained_statement() const;
    private:
        VariantContainedStatement _contained_statement;
    };
}

#endif
