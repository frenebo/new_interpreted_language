#ifndef VIRTUAL_MACHINE_HPP
#define VIRTUAL_MACHINE_HPP

#include "./data_stack/data_stack.hpp"

namespace virtual_machine
{
    class VirtualMachineState
    {
    private:
        virtual_machine::data_stack::DataStack _data_stack;
    };
}

#endif
