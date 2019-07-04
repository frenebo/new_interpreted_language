#include "./data_container_utils.hpp"

namespace virtual_machine::data_container_utils
{
    std::variant<data_container::DataContainer, TypeError> equal_op_containers(const data_container::DataContainer & lhs, const data_container::DataContainer & rhs)
    {
        data_container::DataContainer::VariantDataContainer lhs_contained = lhs.contained();
        data_container::DataContainer::VariantDataContainer rhs_contained = rhs.contained();

        bool lhs_is_float = std::holds_alternative<data_container::FloatContainer>(lhs_contained);
        bool lhs_is_int = std::holds_alternative<data_container::IntegerContainer>(lhs_contained);
        bool lhs_is_number = lhs_is_float || lhs_is_int;
        bool lhs_is_bool = std::holds_alternative<data_container::BoolContainer>(lhs_contained);
        bool lhs_is_string = std::holds_alternative<data_container::StringContainer>(lhs_contained);

        bool rhs_is_float = std::holds_alternative<data_container::FloatContainer>(rhs_contained);
        bool rhs_is_int = std::holds_alternative<data_container::IntegerContainer>(rhs_contained);
        bool rhs_is_number = rhs_is_float || rhs_is_int;
        bool rhs_is_bool = std::holds_alternative<data_container::BoolContainer>(rhs_contained);
        bool rhs_is_string = std::holds_alternative<data_container::StringContainer>(rhs_contained);

        if (lhs_is_number && rhs_is_number)
        {
            if (lhs_is_float || rhs_is_float)
            {
                float lhs_float;
                if (lhs_is_float)
                {
                    lhs_float = std::get<data_container::FloatContainer>(lhs_contained).value();
                }
                else
                {
                    lhs_float = std::get<data_container::IntegerContainer>(lhs_contained).value();
                }

                float rhs_float;
                if (rhs_is_float)
                {
                    rhs_float = std::get<data_container::FloatContainer>(rhs_contained).value();
                }
                else
                {
                    rhs_float = std::get<data_container::IntegerContainer>(rhs_contained).value();
                }

                bool are_equal = lhs_float == rhs_float;
                return data_container::DataContainer(
                    data_container::BoolContainer(are_equal)
                );
            }
            else
            {
                int lhs_int = std::get<data_container::IntegerContainer>(lhs_contained).value();
                int rhs_int = std::get<data_container::IntegerContainer>(rhs_contained).value();

                bool are_equal =  lhs_int == rhs_int;
                return data_container::DataContainer(
                    data_container::BoolContainer(are_equal)
                );
            }
        }
        else if (lhs_is_bool && rhs_is_bool)
        {
            bool lhs_val = std::get<data_container::BoolContainer>(lhs_contained).value();
            bool rhs_val = std::get<data_container::BoolContainer>(rhs_contained).value();

            bool are_equal = lhs_val == rhs_val;

            return data_container::DataContainer(
                data_container::BoolContainer(are_equal)
            );
        }
        else if (lhs_is_string && rhs_is_string)
        {
            const std::string & lhs_val = std::get<data_container::StringContainer>(lhs_contained).value();
            const std::string & rhs_val = std::get<data_container::StringContainer>(rhs_contained).value();

            bool are_equal = lhs_val == rhs_val;

            return data_container::DataContainer(
                data_container::BoolContainer(are_equal)
            );
        }
        else
        {
            return data_container::DataContainer(data_container::BoolContainer(false));
        }
    }
}
