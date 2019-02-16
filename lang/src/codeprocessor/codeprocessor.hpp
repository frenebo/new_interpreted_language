#ifndef CODEPROCESSING_HPP
#define CODEPROCESSING_HPP

#include <string>
#include <variant>

#include "../syntaxtree/statementseries/statementseries.hpp"

namespace codeprocessor
{
    class CodeProcessorError
    {
    public:
        CodeProcessorError(std::string message);
        const std::string & message() const;
    private:
        std::string _message;
    };
    
    std::variant<syntaxtree::statement_series::StatementSeries, CodeProcessorError>
    parse_program(const std::string & text);
}

#endif
