#include "./data_container_utils.hpp"

namespace virtual_machine::data_container_utils
{
    std::variant<data_container::DataContainer, TypeError> get_value_not(const data_container::DataContainer & lhs)
    {
        data_container::DataContainer::VariantDataContainer contained = lhs.contained();

        if (std::holds_alternative<data_container::BoolContainer>(contained))
        {
            bool val = std::get<data_container::BoolContainer>(contained).value();
            bool not_val = !val;

            return data_container::DataContainer(
                data_container::BoolContainer(not_val)
            );
        }
        else
        {
            return TypeError("Invalid 'not' type operation: " + data_container::data_container_type_string(contained));
        }
    }
}