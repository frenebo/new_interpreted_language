#include "./instructions.hpp"

namespace bytecode::instructions
{
    GotoRelativePosition::GotoRelativePosition(int move_distance)
    : _move_distance(move_distance)
    {
    }

    int GotoRelativePosition::move_distance() const
    {
        return _move_distance;
    }
}