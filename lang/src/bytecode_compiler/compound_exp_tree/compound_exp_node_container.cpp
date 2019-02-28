#include "./compound_exp_tree.hpp"

namespace bytecode_compiler::compound_exp_tree
{
    CompoundExpNodeContainer::CompoundExpNodeContainer(VariantCompoundExpNode contained)
    : _contained(contained)
    {
    }

    const CompoundExpNodeContainer::VariantCompoundExpNode & CompoundExpNodeContainer::contained() const
    {
        return _contained;
    }
}