#ifndef PARSED_INFO_HPP
#define PARSED_INFO_HPP

namespace parser
{
    template <class T>
    class ParseResult
    {
    public:
        ParseResult(T contained, unsigned long consumed_count)
        : _consumed_count(consumed_count),
        _contained(contained)
        {
        }
        
        unsigned long consumed_count() const
        {
            return _consumed_count;
        }
        
        const T & contained() const
        {
            return _contained;
        }
    private:
        unsigned long _consumed_count;
        T _contained;
    };
}

#endif
