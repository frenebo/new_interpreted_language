#ifndef VM_DATA_CONTAINER_HPP
#define VM_DATA_CONTAINER_HPP

#include <variant>
#include <string>

namespace virtual_machine::data_container
{
    class IntegerContainer
    {
    public:
        IntegerContainer(int value);
        int value() const;
    private:
        int _value;
    };

    class FloatContainer
    {
    public:
        FloatContainer(float value);
        float value() const;
    private:
        float _value;
    };
    
    class DataContainer
    {
    public:
        typedef std::variant<IntegerContainer, FloatContainer> VariantDataContainer;
        DataContainer(VariantDataContainer contained);

        const VariantDataContainer & contained() const;
    private:
        VariantDataContainer _contained;
    };

    std::string data_container_type_string(DataContainer);
}

#endif
