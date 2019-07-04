#include "./data_container_utils.hpp"

namespace virtual_machine::data_container_utils
{
    std::variant<data_container::DataContainer, TypeError> modulo_data_containers(const data_container::DataContainer & lhs, const data_container::DataContainer & rhs)
    {
        bool lhs_is_int = std::holds_alternative<data_container::IntegerContainer>(lhs.contained());
        bool rhs_is_int = std::holds_alternative<data_container::IntegerContainer>(rhs.contained());

        // number addition
        if (lhs_is_int && rhs_is_int)
        {
            int lhs_val = std::get<data_container::IntegerContainer>(lhs.contained()).value();
            int rhs_val = std::get<data_container::IntegerContainer>(rhs.contained()).value();

            int mod_result = lhs_val % rhs_val;

            return data_container::DataContainer(data_container::IntegerContainer(mod_result));
        }
        else
        {
            return TypeError(
                "Invalid modulo types: " + data_container::data_container_type_string(lhs) + " and " +
                data_container::data_container_type_string(rhs) + ". Must both be integers"
            );
        }
    }
}
