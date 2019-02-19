#include "./data_container.hpp"

namespace virtual_machine::data_container
{
    FloatContainer::FloatContainer(float value)
    : _value(value)
    {
    }

    float FloatContainer::value() const
    {
        return _value;
    }
}
