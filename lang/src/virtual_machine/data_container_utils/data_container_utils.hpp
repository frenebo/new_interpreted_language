#ifndef VM_DATA_CONTAINER_UTILS
#define VM_DATA_CONTAINER_UTILS

#include "../data_container/data_container.hpp"
#include <variant>
#include <string>

namespace virtual_machine::data_container_utils
{
    class ConversionError
    {
    public:
        ConversionError(std::string problem);
        const std::string & problem() const;
    private:
        std::string _problem;
    };

    std::variant<bool, ConversionError> convert_data_to_bool(virtual_machine::data_container::DataContainer data_container);
    
    std::variant<bool, data_container::DataContainer> add_data_containers(data_container::DataContainer lhs, data_container::DataContainer rhs);
    std::variant<bool, data_container::DataContainer> subtract_data_containers(data_container::DataContainer lhs, data_container::DataContainer rhs);
}

#endif
