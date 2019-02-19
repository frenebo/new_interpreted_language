#include "./data_container.hpp"

namespace virtual_machine::data_container
{
    IntegerContainer::IntegerContainer(int value)
    : _value(value)
    {
    }

    int IntegerContainer::value() const
    {
        return _value;
    }
}
