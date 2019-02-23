#include "./data_container.hpp"

namespace virtual_machine::data_container
{
    std::string data_container_type_string(DataContainer container)
    {
        auto contained = container.contained();
        if (std::holds_alternative<IntegerContainer>(contained))
        {
            return "Integer";
        }
        else if (std::holds_alternative<FloatContainer>(contained))
        {
            return "Float";
        }
        else
        {
            return "Unimplemented data container string";
        }
    }
}
