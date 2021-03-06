#include "./data_container.hpp"

namespace virtual_machine::data_container
{
    IntegerContainer::IntegerContainer(long value)
    : _value(value)
    {
    }

    long IntegerContainer::value() const
    {
        return _value;
    }
}
