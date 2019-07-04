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

    class CompoundExpressionStatement
    {
    public:
        CompoundExpressionStatement(syntax_tree::compound_expression::CompoundExpression compound_exp);
        const syntax_tree::compound_expression::CompoundExpression & compound_exp() const;
    private:
        syntax_tree::compound_expression::CompoundExpression _compound_exp;
    };

    /*
     * This class is necessary because classes cannot contain each other
     *
     * A statement series would contain statements, which would contain an if statement, which would
     * contain a statement series, which would contain an if statement, etc.
     *
     * This way, the if statement will not contain a statement sequence in full, only
     * a pointer to one.
     */

    class ContainableStatementSeries
    {
    public:
        ContainableStatementSeries(syntax_tree::statement_series::StatementSeries statement_series);
        const syntax_tree::statement_series::StatementSeries & statement_series() const;

        ~ContainableStatementSeries();
        ContainableStatementSeries(const ContainableStatementSeries &);
        ContainableStatementSeries & operator=(const ContainableStatementSeries & rhs);
    private:
        std::unique_ptr<syntax_tree::statement_series::StatementSeries> _statement_series;
    };

    class IfStatement
    {
    public:
        IfStatement(syntax_tree::compound_expression::CompoundExpression if_condition, syntax_tree::statement_series::StatementSeries body_statement_series);
        const syntax_tree::compound_expression::CompoundExpression & if_condition() const;
        const syntax_tree::statement_series::StatementSeries & body_statement_series() const;
    private:
        syntax_tree::compound_expression::CompoundExpression _if_condition;
        ContainableStatementSeries _body_statement_series;
    };

    class ForLoopStatement
    {
    public:
        ForLoopStatement(
            syntax_tree::compound_expression::CompoundExpression setup_expression,
            syntax_tree::compound_expression::CompoundExpression condition_expression,
            syntax_tree::compound_expression::CompoundExpression increment_expression,
            syntax_tree::statement_series::StatementSeries loop_body
        );
        const syntax_tree::compound_expression::CompoundExpression & setup_expression() const;
        const syntax_tree::compound_expression::CompoundExpression & condition_expression() const;
        const syntax_tree::compound_expression::CompoundExpression & increment_expression() const;
        const syntax_tree::statement_series::StatementSeries & loop_body() const;
    private:
        syntax_tree::compound_expression::CompoundExpression _setup_expression;
        syntax_tree::compound_expression::CompoundExpression _condition_expression;
        syntax_tree::compound_expression::CompoundExpression _increment_expression;
        ContainableStatementSeries _loop_body;
    };

    class StatementContainer
    {
    public:
        typedef std::variant<
            CompoundExpressionStatement,
            PrintStatement,
            IfStatement,
            ForLoopStatement
        > VariantContainedStatement;

        StatementContainer(VariantContainedStatement contained_statement);

        const VariantContainedStatement & contained_statement() const;
    private:
        VariantContainedStatement _contained_statement;
    };
}

#endif
