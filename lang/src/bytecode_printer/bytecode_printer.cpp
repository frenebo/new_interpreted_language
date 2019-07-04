#include <iostream>
#include "./bytecode_printer.hpp"

namespace bytecode_printer
{
    void print_instructions(const std::vector<bytecode::instructions::InstructionContainer> & instruction_containers)
    {
        for (const bytecode::instructions::InstructionContainer & instruction_container : instruction_containers)
        {
            print_instruction(instruction_container);
        }
    }

    void print_instruction(const bytecode::instructions::InstructionContainer & instruction_container)
    {
        const bytecode::instructions::InstructionContainer::VariantInstruction & contained_instruction =
            instruction_container.contained_instruction();

        if (std::holds_alternative<bytecode::instructions::StackAdd>(contained_instruction))
        {
            std::cout << "ADD\n";
        }
        else if (std::holds_alternative<bytecode::instructions::StackDivide>(contained_instruction))
        {
            std::cout << "DIVIDE\n";
        }
        else if (std::holds_alternative<bytecode::instructions::StackFloatPushConst>(contained_instruction))
        {
            float val = std::get<bytecode::instructions::StackFloatPushConst>(contained_instruction).value();
            std::cout << "PUSH FLOAT CONST: " << val << "\n";
        }
        else if (std::holds_alternative<bytecode::instructions::StackIntegerPushConst>(contained_instruction))
        {
            int val = std::get<bytecode::instructions::StackIntegerPushConst>(contained_instruction).value();
            std::cout << "PUSH INT CONST: " << val << "\n";
        }
        else if (std::holds_alternative<bytecode::instructions::StackLoadFromVariable>(contained_instruction))
        {
            std::string var_name = std::get<bytecode::instructions::StackLoadFromVariable>(contained_instruction).var_name();
            std::cout << "LOAD VAR: " << var_name << "\n";
        }
        else if (std::holds_alternative<bytecode::instructions::StackMultiply>(contained_instruction))
        {
            std::cout << "MULTIPLY\n";
        }
        else if (std::holds_alternative<bytecode::instructions::StackPop>(contained_instruction))
        {
            std::cout << "POP\n";
        }
        else if (std::holds_alternative<bytecode::instructions::StackPrint>(contained_instruction))
        {
            std::cout << "PRINT\n";
        }
        else if (std::holds_alternative<bytecode::instructions::StackStoreToVariable>(contained_instruction))
        {
            std::string var_name = std::get<bytecode::instructions::StackStoreToVariable>(contained_instruction).var_name();
            std::cout << "STORE VAR: " << var_name << "\n";
        }
        else if (std::holds_alternative<bytecode::instructions::GotoRelativePosition>(contained_instruction))
        {
            int move_dist = std::get<bytecode::instructions::GotoRelativePosition>(contained_instruction).move_distance();
            std::cout << "GOTO RELATIVE POSITION: " << move_dist << "\n";
        }
        else if (std::holds_alternative<bytecode::instructions::SkipNextInstructionIfStackValueTruthy>(contained_instruction))
        {
            std::cout << "SKIP NEXT INSTRUCTION IF STACK VALUE TRUTHY\n";
        }
        else if (std::holds_alternative<bytecode::instructions::SkipNextInstructionIfStackValueTruthy>(contained_instruction))
        {
            std::cout << "SKIP NEXT INSTRUCTION IF STACK VALUE FALSY\n";
        }
        else if (std::holds_alternative<bytecode::instructions::StackDuplicate>(contained_instruction))
        {
            std::cout << "STACK DUPLICATE\n";
        }
        else if (std::holds_alternative<bytecode::instructions::StackCompareLessThan>(contained_instruction))
        {
            std::cout << "STACK COMPARE LESS THAN\n";
        }
        else if (std::holds_alternative<bytecode::instructions::StackCompareLessThanOrEqualTo>(contained_instruction))
        {
            std::cout << "STACK COMPARE LESS THAN OR EQUAL TO\n";
        }
        else if (std::holds_alternative<bytecode::instructions::StackApplyNot>(contained_instruction))
        {
            std::cout << "STACK APPLY NOT OPERATION\n";
        }
        else if (std::holds_alternative<bytecode::instructions::StackModuloOperation>(contained_instruction))
        {
            std::cout << "STACK MODULO OPERATION\n";
        }
        else if (std::holds_alternative<bytecode::instructions::StackBoolPushConst>(contained_instruction))
        {
            auto bool_push_const_instruction = std::get<bytecode::instructions::StackBoolPushConst>(contained_instruction);

            std::cout << "PUSH BOOL CONST: " << bool_push_const_instruction.value() << "\n";
        }
        else if (std::holds_alternative<bytecode::instructions::StackStringPushConst>(contained_instruction))
        {
            auto string_push_const_instruction = std::get<bytecode::instructions::StackStringPushConst>(contained_instruction);

            std::cout << "PUSH STRING CONST: \"" << string_push_const_instruction.value() << "\"\n";
        }
        else
        {
            std::cout << "unimplemented bytecode instruction print\n";
        }
    }
}