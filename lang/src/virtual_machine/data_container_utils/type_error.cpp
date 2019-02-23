#include "./data_container_utils.hpp"

namespace virtual_machine::data_container_utils
{
    TypeError::TypeError(std::string problem)
    : _problem(problem)
    {
    }

    const std::string & TypeError::problem() const
    {
        return _problem;
    }
}
