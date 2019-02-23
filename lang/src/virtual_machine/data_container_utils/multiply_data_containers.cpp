#include "./data_container_utils.hpp"

namespace virtual_machine::data_container_utils
{
    std::variant<data_container::DataContainer, TypeError> multiply_data_containers(const data_container::DataContainer & lhs, const data_container::DataContainer & rhs)
    {
        bool lhs_is_int = std::holds_alternative<data_container::IntegerContainer>(lhs.contained());
        bool rhs_is_int = std::holds_alternative<data_container::IntegerContainer>(rhs.contained());

        bool lhs_is_float = std::holds_alternative<data_container::FloatContainer>(lhs.contained());
        bool rhs_is_float = std::holds_alternative<data_container::FloatContainer>(rhs.contained());

        bool lhs_is_number = lhs_is_int || lhs_is_float;
        bool rhs_is_number = rhs_is_int || rhs_is_float;

        // number addition
        if (lhs_is_number && rhs_is_number)
        {
            // int addition
            if (lhs_is_int && rhs_is_int)
            {
                int lhs_val = std::get<data_container::IntegerContainer>(lhs.contained()).value();
                int rhs_val = std::get<data_container::IntegerContainer>(rhs.contained()).value();
                int product = lhs_val * rhs_val;

                return data_container::DataContainer(data_container::IntegerContainer(product));
            }
            // float addition
            else
            {
                float lhs_val;
                float rhs_val;
                if (lhs_is_float)
                {
                    lhs_val = std::get<data_container::FloatContainer>(lhs.contained()).value();
                }
                else
                {
                    lhs_val = std::get<data_container::IntegerContainer>(lhs.contained()).value();
                }

                if (rhs_is_float)
                {
                    rhs_val = std::get<data_container::FloatContainer>(rhs.contained()).value();
                }
                else
                {
                    rhs_val = std::get<data_container::IntegerContainer>(rhs.contained()).value();
                }

                float product = lhs_val * rhs_val;

                return data_container::DataContainer(data_container::FloatContainer(product));
            }
        }
        else
        {
            return TypeError(
                "Incompatible addition types: " + data_container::data_container_type_string(lhs) + " and " +
                data_container::data_container_type_string(rhs)
            );
        }
    }
}
