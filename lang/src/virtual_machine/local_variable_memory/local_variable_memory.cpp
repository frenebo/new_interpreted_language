#include "./local_variable_memory.hpp"

namespace virtual_machine::local_variable_memory
{
    LocalVariableMemory::LocalVariableMemory()
    : _variable_data()
    {
    }

    std::vector<std::string> LocalVariableMemory::all_variable_names() const
    {
        std::vector<std::string> names;
        names.reserve(_variable_data.size());
        for (auto const& imap: _variable_data)
        {
            names.push_back(imap.first);
        }

        return names;
    }

    bool LocalVariableMemory::variable_exists(std::string var_name) const
    {
        return _variable_data.count(var_name) != 0;
    }

    std::optional<data_container::DataContainer> LocalVariableMemory::get_variable(std::string var_name) const
    {
        auto find_iterator_pos = _variable_data.find(var_name);
        
        if (find_iterator_pos == _variable_data.end())
        {
            return std::optional<data_container::DataContainer>();
        }
        else
        {
            return find_iterator_pos->second;
        }
    }

    void LocalVariableMemory::set_variable(std::string var_name, data_container::DataContainer variable_value)
    {
        auto find_var = _variable_data.find(var_name);
        if (find_var != _variable_data.end())
        {
            _variable_data.erase(find_var);
        }
        _variable_data.insert(std::make_pair(var_name, variable_value));
    }
}
