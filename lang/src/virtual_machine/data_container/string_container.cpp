#include "./data_container.hpp"

namespace virtual_machine::data_container
{
    StringContainer::StringContainer(std::string value)
    : _value(value)
    {
    }

    const std::string & StringContainer::value() const
    {
        return _value;
    }
}
