#include "./data_container.hpp"

namespace virtual_machine::data_container
{
    BoolContainer::BoolContainer(bool value)
    : _value(value)
    {
    }

    bool BoolContainer::value() const
    {
        return _value;
    }
}