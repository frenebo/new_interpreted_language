#ifndef VM_DATA_CONTAINER_HPP
#define VM_DATA_CONTAINER_HPP

#include <variant>
#include <string>

namespace virtual_machine::data_container
{
    class IntegerContainer
    {
    public:
        IntegerContainer(long value);
        long value() const;
    private:
        long _value;
    };

    class FloatContainer
    {
    public:
        FloatContainer(float value);
        float value() const;
    private:
        float _value;
    };

    class BoolContainer
    {
    public:
        BoolContainer(bool value);
        bool value() const;
    private:
        bool _value;
    };

    class StringContainer
    {
    public:
        StringContainer(std::string value);
        const std::string & value() const;
    private:
        std::string _value;
    };

    class DataContainer
    {
    public:
        typedef std::variant<
            IntegerContainer,
            FloatContainer,
            BoolContainer,
            StringContainer
        > VariantDataContainer;

        DataContainer(VariantDataContainer contained);

        const VariantDataContainer & contained() const;
    private:
        VariantDataContainer _contained;
    };

    std::string data_container_type_string(DataContainer);
}

#endif
