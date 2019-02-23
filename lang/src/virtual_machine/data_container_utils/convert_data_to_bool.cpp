#include <iostream>
#include "./data_container_utils.hpp"

namespace virtual_machine::data_container_utils
{
    std::variant<bool, TypeError> convert_data_to_bool(const virtual_machine::data_container::DataContainer & data_container)
    {
        auto contained = data_container.contained();
        if (std::holds_alternative<data_container::FloatContainer>(contained))
        {
            float val = std::get<data_container::FloatContainer>(contained).value();
            return val != 0;
        }
        else if (std::holds_alternative<data_container::IntegerContainer>(contained))
        {
            int val = std::get<data_container::IntegerContainer>(contained).value();
            return val != 0;
        }
        else
        {
            return TypeError("Unimplemented data type for conversion to bool\n");
        }
    }
}
