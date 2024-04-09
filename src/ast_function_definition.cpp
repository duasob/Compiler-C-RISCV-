
#include "ast_function_definition.hpp"



void FunctionDefinition::EmitRISC(std::ostream &stream, Context &context) const
{

    stream << ".text" << std::endl;
    stream << ".globl " << declarator_->GetStr() << std::endl;
    stream << ".type " << declarator_->GetStr() << ", @function" << std::endl;
    stream << declarator_->GetStr() << ":" << std::endl;
    stream << "li t0, 1" << std::endl;
    context.functionType.push_back(declaration_specifiers_->GetStr());

    context.AddScopeTree("function", nullptr, stream);
    context.stackSize.push_back(EmitStackPointerOpen(stream, context));
    context.storeLoad = 0;
    declarator_->EmitRISC(stream, context);


    if (compound_statement_ != nullptr)
    {
        compound_statement_->EmitRISC(stream, context);
    }

    if(declaration_specifiers_->GetStr() == "void"){
        stream << "lw ra, " << context.stackSize.back() - 4 << "(sp)" << std::endl;
        stream << "lw " << " s0, " << context.stackSize.back() - 8 << "(sp)" << std::endl;
        stream << "lw " << " s1, " << context.stackSize.back() - 12 << "(sp)" << std::endl;
        stream << "addi sp, sp, " << context.stackSize.back() << std::endl;
        stream << "jr ra" << std::endl;
    }

    //remove the function from the scope
    context.RemoveScopeTree();
    context.functionType.pop_back();
    context.currentScope->variableOffsetMap.clear();
    context.stackSize.pop_back();
    context.parameterStackSize = 0;
    context.parameterStackPointer = 0;
    context.statementStackPointer.pop_back();
    context.statementStackSize.pop_back();
    context.opReg = 0;
    context.paramInitMap.clear();


    for (const auto& pair : context.floatConstMap) {
        stream << pair.first << ":" << std::endl << "    .word " << pair.second << std::endl;
    }
    for (const auto& pair : context.stringDeclareMap) {
        stream << ".section .rodata" << std::endl;
        stream << pair.first << ":" << std::endl << "    .string " << pair.second << std::endl;
    }
}

void FunctionDefinition::Print(std::ostream &stream) const
{
    declaration_specifiers_->Print(stream);
    stream << " ";

    declarator_->Print(stream);
    stream << std::endl;


    if (compound_statement_ != nullptr)
    {
        compound_statement_->Print(stream);
    }

}

int FunctionDefinition::EmitStackPointerOpen(std::ostream &stream, Context &context) const
{
    context.parameterStackSize = declarator_->GetParamSize()== 0 ? 0 : 16 + 16*(declarator_->GetParamSize()/4);
    int stack_size = 16 + context.parameterStackSize;

    stream << "addi sp, sp, -" << stack_size << std::endl;
    stream << "sw ra, " << stack_size - 4 << "(sp)" << std::endl;
    stream << "sw s0, " << stack_size - 8 << "(sp)" << std::endl;
    stream << "sw s1, " << stack_size - 12<< "(sp)" << std::endl;
    stream << "addi s0, sp, " << stack_size << std::endl;

    return stack_size;
}


