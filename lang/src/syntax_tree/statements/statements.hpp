#ifndef SYNTAX_TREE_STATEMENTS_HPP
#define SYNTAX_TREE_STATEMENTS_HPP

#include <variant>
#include <memory>

#include "../compound_expression/compound_expression.hpp"

namespace syntax_tree::statement_series
{
    class StatementSeries;
}

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

    class IfStatement
    {
    public:
        IfStatement(syntax_tree::compound_expression::CompoundExpression if_condition, syntax_tree::statement_series::StatementSeries body_statement_series);
        const syntax_tree::compound_expression::CompoundExpression & if_condition() const;
        const syntax_tree::statement_series::StatementSeries & body_statement_series() const;

        ~IfStatement();
        IfStatement(const IfStatement &);

        IfStatement & operator=(const IfStatement & rhs);
    private:
        syntax_tree::compound_expression::CompoundExpression _if_condition;
        std::unique_ptr<syntax_tree::statement_series::StatementSeries> _body_statement_series;
    };
    
    class StatementContainer
    {
    public:
        typedef std::variant<
            CompoundExpressionStatement,
            PrintStatement,
            IfStatement,
            AssignmentStatement
        > VariantContainedStatement;
        
        StatementContainer(VariantContainedStatement contained_statement);
        
        const VariantContainedStatement & contained_statement() const;
    private:
        VariantContainedStatement _contained_statement;
    };
}

#endif
