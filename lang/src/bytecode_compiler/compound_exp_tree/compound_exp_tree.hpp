#ifndef BYTECODE_COMPILER_COMPOUND_EXP_TREE_HPP
#define BYTECODE_COMPILER_COMPOUND_EXP_TREE_HPP

#include <memory>
#include <string>

#include "../../syntax_tree/compound_expression/compound_expression.hpp"
#include "../../bytecode/instructions/instructions.hpp"

namespace bytecode_compiler::compound_exp_tree
{
    class CompoundExpValueNode
    {
    public:
        CompoundExpValueNode(std::vector<bytecode::instructions::InstructionContainer> instructions);
        const std::vector<bytecode::instructions::InstructionContainer> & instructions() const;
    private:
        std::vector<bytecode::instructions::InstructionContainer> _instructions;
    };

    class CompoundExpVariableNode
    {
    public:
        CompoundExpVariableNode(std::string variable_name);
        const std::string & variable_name() const;
    private:
        std::string _variable_name;
    };

    class CompoundExpNodeContainer;

    class CompoundExpOpNode
    {
    public:
        CompoundExpOpNode(CompoundExpNodeContainer lhs, syntax_tree::compound_expression::OperatorType op_type, CompoundExpNodeContainer rhs);

        ~CompoundExpOpNode();

        CompoundExpOpNode(const CompoundExpOpNode & other);

        CompoundExpOpNode & operator=(const CompoundExpOpNode & other);

        const CompoundExpNodeContainer & lhs() const;

        syntax_tree::compound_expression::OperatorType op_type() const;

        const CompoundExpNodeContainer & rhs() const;
    private:
        std::unique_ptr<CompoundExpNodeContainer> _lhs;
        syntax_tree::compound_expression::OperatorType _op_type;
        std::unique_ptr<CompoundExpNodeContainer> _rhs;
    };
    
    class CompoundExpNodeContainer
    {
    public:
        typedef std::variant<
            CompoundExpVariableNode,
            CompoundExpValueNode,
            CompoundExpOpNode
        > VariantCompoundExpNode;
        
        CompoundExpNodeContainer(VariantCompoundExpNode contained);

        const VariantCompoundExpNode & contained() const;
    private:
        VariantCompoundExpNode _contained;
    };

    

    
    
}

#endif
