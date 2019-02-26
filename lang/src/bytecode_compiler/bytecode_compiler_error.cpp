#include "./bytecode_compiler.hpp"

namespace bytecode_compiler
{
    BytecodeCompilerError::BytecodeCompilerError(std::string message)
    : _message(message)
    {
    }

    const std::string & BytecodeCompilerError::message() const
    {
        return _message;
    }
}