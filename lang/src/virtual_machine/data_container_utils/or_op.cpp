#include "./data_container_utils.hpp"

namespace virtual_machine::data_container_utils
{
    std::variant<data_container::DataContainer, TypeError> or_op(const data_container::DataContainer & lhs, const data_container::DataContainer & rhs)
    {
        data_container::DataContainer::VariantDataContainer lhs_contained = lhs.contained();
        data_container::DataContainer::VariantDataContainer rhs_contained = rhs.contained();

        if (std::holds_alternative<data_container::BoolContainer>(lhs_contained) &&
            std::holds_alternative<data_container::BoolContainer>(rhs_contained))
        {
            bool lhs_val = std::get<data_container::BoolContainer>(lhs_contained).value();
            bool rhs_val = std::get<data_container::BoolContainer>(rhs_contained).value();

            bool or_val = lhs_val || rhs_val;

            return data_container::DataContainer(
                data_container::BoolContainer(or_val)
            );
        }
        else
        {
            return TypeError(
                "Invalid types for 'or' operation: " +
                data_container::data_container_type_string(lhs) +
                ", " + data_container::data_container_type_string(rhs)
            );
        }
    }
}