#include "./data_container_utils.hpp"

namespace virtual_machine::data_container_utils
{
    ConversionError::ConversionError(std::string problem)
    : _problem(problem)
    {
    }

    const std::string & ConversionError::problem() const
    {
        return _problem;
    }
}