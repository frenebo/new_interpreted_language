#ifndef CODEPROCESSING_HPP
#define CODEPROCESSING_HPP

#include <string>
#include <variant>

#include "../syntaxtree/statementseries/statementseries.hpp"

namespace codeprocessor
{
    class CodeProcessorError
    {
        std::string _message;
    public:
        CodeProcessorError(std::string message);
        const std::string & message() const;
    };
    
    std::variant<syntaxtree::statement_series::StatementSeries, CodeProcessorError>
    parse_program(const std::string & text);
    
    void helloworld();
}

#endif
