#ifndef VM_LOCAL_VARIABLE_MEMORY_HPP
#define VM_LOCAL_VARIABLE_MEMORY_HPP

#include <map>
#include <string>
#include <vector>
#include <optional>

#include "../data_container/data_container.hpp"

namespace virtual_machine::local_variable_memory
{
    class LocalVariableMemory
    {
    public:
        LocalVariableMemory();
        
        std::vector<std::string> all_variable_names() const;
        bool variable_exists(std::string var_name) const;
        std::optional<data_container::DataContainer> get_variable(std::string var_name) const;
        void set_variable(std::string var_name, data_container::DataContainer variable_value);
        // std::map<std::string, data_container::DataContainer> & variable_data();
    private:
        std::map<std::string, data_container::DataContainer> _variable_data;
    };
}

#endif
