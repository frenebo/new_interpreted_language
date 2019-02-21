#ifndef VM_DATA_STACK
#define VM_DATA_STACK

#include <vector>
#include <optional>

#include "../data_container/data_container.hpp"

namespace virtual_machine::data_stack
{
    class DataStack
    {
    public:
        DataStack();
        void push(data_container::DataContainer data_container);
        std::optional<data_container::DataContainer> pop();
        size_t size() const;
    private:
        std::vector<data_container::DataContainer> _stack;
    };
}

#endif
