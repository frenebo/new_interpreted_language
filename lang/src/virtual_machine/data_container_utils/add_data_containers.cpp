#include "./data_container_utils.hpp"

namespace virtual_machine::data_container_utils
{
    std::variant<data_container::DataContainer, TypeError> add_data_containers(const data_container::DataContainer & lhs, const data_container::DataContainer & rhs)
    {
        bool lhs_is_int = std::holds_alternative<data_container::IntegerContainer>(lhs.contained());
        bool rhs_is_int = std::holds_alternative<data_container::IntegerContainer>(rhs.contained());

        bool lhs_is_float = std::holds_alternative<data_container::FloatContainer>(lhs.contained());
        bool rhs_is_float = std::holds_alternative<data_container::FloatContainer>(rhs.contained());

        bool lhs_is_number = lhs_is_int || lhs_is_float;
        bool rhs_is_number = rhs_is_int || rhs_is_float;

        bool lhs_is_string = std::holds_alternative<data_container::StringContainer>(lhs.contained());
        bool rhs_is_string = std::holds_alternative<data_container::StringContainer>(rhs.contained());

        // number addition
        if (lhs_is_number && rhs_is_number)
        {
            // int addition
            if (lhs_is_int && rhs_is_int)
            {
                int lhs_val = std::get<data_container::IntegerContainer>(lhs.contained()).value();
                int rhs_val = std::get<data_container::IntegerContainer>(rhs.contained()).value();
                int sum = lhs_val + rhs_val;

                return data_container::DataContainer(data_container::IntegerContainer(sum));
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

                float sum = lhs_val + rhs_val;

                return data_container::DataContainer(data_container::FloatContainer(sum));
            }
        }
        else if (lhs_is_string && rhs_is_string)
        {
            const std::string & lhs_value = std::get<data_container::StringContainer>(lhs.contained()).value();
            const std::string & rhs_value = std::get<data_container::StringContainer>(rhs.contained()).value();

            return data_container::DataContainer(data_container::StringContainer(lhs_value + rhs_value));
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
