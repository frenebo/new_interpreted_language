#ifndef STATEMENTS_HPP
#define STATEMENTS_HPP

#include <variant>

namespace syntax_tree::statements
{
    class ComplexExpressionStatement
    {
    public:
        ComplexExpressionStatement();
    };
    
    class StatementContainer
    {
    public:
        typedef std::variant<ComplexExpressionStatement> VariantContainedStatement;
        
        StatementContainer(VariantContainedStatement contained_statement);
        
        const VariantContainedStatement & contained_statement() const;
    private:
        VariantContainedStatement _contained_statement;
    };
}

#endif
