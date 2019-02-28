#include "./bytecode_compiler.hpp"

namespace bytecode_compiler
{
    void BytecodeCompiler::push_instructions(InstructionsVec & target_vec, const InstructionsVec & source_vec)
    {
        target_vec.insert(target_vec.end(), source_vec.begin(), source_vec.end());
    }
}