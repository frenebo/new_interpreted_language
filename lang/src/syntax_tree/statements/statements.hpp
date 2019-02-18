#ifndef STATEMENTS_HPP
#define STATEMENTS_HPP

#include "../compound_expression/compound_expression.hpp"
#include <variant>

namespace syntax_tree::statements
{
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
        typedef std::variant<CompoundExpressionStatement> VariantContainedStatement;
        
        StatementContainer(VariantContainedStatement contained_statement);
        
        const VariantContainedStatement & contained_statement() const;
    private:
        VariantContainedStatement _contained_statement;
    };
}

#endif
