#include "./data_container.hpp"

namespace virtual_machine::data_container
{
    DataContainer::DataContainer(VariantDataContainer contained)
    : _contained(contained)
    {
    }

    const DataContainer::VariantDataContainer &
    DataContainer::contained() const
    {
        return _contained;
    }
}