#include "./data_container_utils.hpp"

namespace virtual_machine::data_container_utils
{
    std::variant<data_container::DataContainer, TypeError> less_than_or_equal_op_containers(const data_container::DataContainer & lhs, const data_container::DataContainer & rhs)
    {
        data_container::DataContainer::VariantDataContainer lhs_contained = lhs.contained();
        data_container::DataContainer::VariantDataContainer rhs_contained = rhs.contained();
        
        bool lhs_is_float = std::holds_alternative<data_container::FloatContainer>(lhs_contained);
        bool lhs_is_int = std::holds_alternative<data_container::IntegerContainer>(lhs_contained);
        bool lhs_is_number = lhs_is_float || lhs_is_int;

        bool rhs_is_float = std::holds_alternative<data_container::FloatContainer>(rhs_contained);
        bool rhs_is_int = std::holds_alternative<data_container::IntegerContainer>(rhs_contained);
        bool rhs_is_number = rhs_is_float || rhs_is_int;

        if (!lhs_is_number)
        {
            return TypeError("Invalid left hand side type for comparison: " + data_container::data_container_type_string(lhs_contained));
        }
        
        if (!rhs_is_number)
        {
            return TypeError("Invalid right hand side type for comparison: " + data_container::data_container_type_string(rhs_contained));
        }

        // float comparison
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

            bool is_less_than_or_equal_to = lhs_float <= rhs_float;
            return data_container::DataContainer(
                data_container::BoolContainer(is_less_than_or_equal_to)
            );
        }
        else
        {
            int lhs_int = std::get<data_container::IntegerContainer>(lhs_contained).value();
            int rhs_int = std::get<data_container::IntegerContainer>(rhs_contained).value();

            bool is_less_than_or_equal_to =  lhs_int <= rhs_int;
            return data_container::DataContainer(
                data_container::BoolContainer(is_less_than_or_equal_to)
            );
        }
    }
}
