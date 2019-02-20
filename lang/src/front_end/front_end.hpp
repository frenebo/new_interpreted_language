#ifndef FRONT_END_HPP
#define FRONT_END_HPP

#include <string>
#include <variant>

#include "../syntax_tree/statement_series/statement_series.hpp"

namespace front_end
{
    class FrontEndError
    {
    public:
        FrontEndError(std::string message);
        const std::string & message() const;
    private:
        std::string _message;
    };
    
    std::variant<syntax_tree::statement_series::StatementSeries, FrontEndError>
    parse_program(const std::string & text);
}

#endif
