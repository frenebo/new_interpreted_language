#ifndef VM_DATA_CONTAINER_UTILS
#define VM_DATA_CONTAINER_UTILS

#include "../data_container/data_container.hpp"
#include <variant>
#include <string>

namespace virtual_machine::data_container_utils
{
    class TypeError
    {
    public:
        TypeError(std::string problem);
        const std::string & problem() const;
    private:
        std::string _problem;
    };

    std::variant<bool, TypeError> convert_data_to_bool(const data_container::DataContainer & data_container);
    std::variant<data_container::DataContainer, TypeError> add_data_containers(const data_container::DataContainer & lhs, const data_container::DataContainer & rhs);
    std::variant<data_container::DataContainer, TypeError> subtract_data_containers(const data_container::DataContainer & lhs, const data_container::DataContainer & rhs);
    std::variant<data_container::DataContainer, TypeError> multiply_data_containers(const data_container::DataContainer & lhs, const data_container::DataContainer & rhs);
}

#endif
