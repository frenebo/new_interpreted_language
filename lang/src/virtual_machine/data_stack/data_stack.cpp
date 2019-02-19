#include "./data_stack.hpp"

namespace virtual_machine::data_stack
{
    DataStack::DataStack()
    {
        _stack = std::vector<data_container::DataContainer>();
    }

    data_container::DataContainer DataStack::pop()
    {
        data_container::DataContainer last = _stack.back();
        
        _stack.pop_back();

        return last;
    }

    void DataStack::push(data_container::DataContainer data_container)
    {
        _stack.push_back(data_container);
    }

    size_t DataStack::size() const
    {
        return _stack.size();
    }
}
