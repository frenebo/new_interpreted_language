#ifndef SYNTAX_TREE_STATEMENTS_HPP
#define SYNTAX_TREE_STATEMENTS_HPP

#include <variant>
#include <memory>
#include <vector>
#include <optional>

#include "../compound_expression/compound_expression.hpp"

namespace syntax_tree::statements
{
    class StatementContainer;
}

namespace syntax_tree::statement_series
{
    class StatementSeries
    {
    public:
        StatementSeries(std::vector<syntax_tree::statements::StatementContainer> statements);
        const std::vector<syntax_tree::statements::StatementContainer> & statements() const;
    private:
        std::vector<syntax_tree::statements::StatementContainer> _statements;
    };
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
    template<class T>
    class PointerHolder
    {
    public:
        PointerHolder(T contained)
        : _contained(std::make_unique<T>(contained))
        {
        }
        const T & contained() const
        {
            return *_contained;
        }

        ~PointerHolder()
        {
            _contained.reset(nullptr);
        }
        PointerHolder(const PointerHolder & rhs)
        : _contained(std::make_unique<T>(rhs.contained()))
        {
        }

        PointerHolder & operator=(const PointerHolder & rhs)
        {
            _contained.reset(nullptr);
            _contained = std::make_unique<T>(rhs.contained());

            return *this;
        }
    private:
        std::unique_ptr<T> _contained;
    };

    class IfStatement;

    class PlainElseBlock
    {
    public:
        PlainElseBlock(syntax_tree::statement_series::StatementSeries body_statement_series);
        const syntax_tree::statement_series::StatementSeries & body_statement_series() const;
    private:
        PointerHolder<syntax_tree::statement_series::StatementSeries> _body_statement_series;
    };

    class ElseIfBlock
    {
    public:
        ElseIfBlock(IfStatement if_statement);
        const IfStatement & if_statement() const;
    private:
        PointerHolder<IfStatement> _if_statement;
    };

    class IfStatement
    {
    public:
        typedef std::optional<std::variant<PlainElseBlock, ElseIfBlock>> OptionalElseVariant;
        IfStatement(
            syntax_tree::compound_expression::CompoundExpression if_condition,
            syntax_tree::statement_series::StatementSeries body_statement_series,
            OptionalElseVariant else_block
        );
        const syntax_tree::compound_expression::CompoundExpression & if_condition() const;
        const syntax_tree::statement_series::StatementSeries & body_statement_series() const;
        const OptionalElseVariant & else_block() const;
    private:
        syntax_tree::compound_expression::CompoundExpression _if_condition;
        PointerHolder<syntax_tree::statement_series::StatementSeries> _body_statement_series;
        OptionalElseVariant _else_block;
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
        PointerHolder<syntax_tree::statement_series::StatementSeries> _loop_body;
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
