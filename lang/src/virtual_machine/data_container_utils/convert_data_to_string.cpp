#include "./data_container_utils.hpp"

namespace virtual_machine::data_container_utils
{
    std::variant<std::string, TypeError> convert_data_to_string(const data_container::DataContainer & data_container)
    {
        auto contained = data_container.contained();
        if (std::holds_alternative<data_container::FloatContainer>(contained))
        {
            float val = std::get<data_container::FloatContainer>(contained).value();
            return std::to_string(val);
        }
        else if (std::holds_alternative<data_container::IntegerContainer>(contained))
        {
            int val = std::get<data_container::IntegerContainer>(contained).value();
            return std::to_string(val);
        }
        else if (std::holds_alternative<data_container::BoolContainer>(contained))
        {
            bool val = std::get<data_container::BoolContainer>(contained).value();
            if (val) return "true";
            else  return "false";
        }
        else
        {
            return TypeError("Unimplemented string conversion for " + data_container::data_container_type_string(data_container));
        }
    }
}
