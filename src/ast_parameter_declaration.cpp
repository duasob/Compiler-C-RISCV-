#include "ast_parameter_declaration.hpp"

void ParameterDeclaration::EmitRISC(std::ostream &stream, Context &context) const
{
    context.currentScope->variableTypeMap[init_declarator_->GetStr()] = declaration_specifiers_->GetStr();
    if (init_declarator_->IsPointer()){
        context.currentScope->arrayTypeMap[init_declarator_->GetStr()] = "pointer";
    }
    int offset = context.calculateParamOffset(init_declarator_->GetStr(), stream);
        if (declaration_specifiers_->GetStr() == "int"){
            stream << "sw a" << context.paramInitMap["int"]++ << ",-" << offset << "(s0)" << std::endl;

        }else if (declaration_specifiers_->GetStr() == "float"){
            stream << "fsw fa" << context.paramInitMap["float"]++ << ",-" << offset << "(s0)" << std::endl;
        }else if (declaration_specifiers_->GetStr() == "double"){
            stream << "fsd fa" << context.paramInitMap["double"]++ << ",-" << offset << "(s0)" << std::endl;
        }else if (declaration_specifiers_->GetStr() == "unsigned"){
            stream << "sw a" << context.paramInitMap["int"]++ << ",-" << offset << "(s0)" << std::endl;
        }

    context.currentScope->variableOffsetMap[init_declarator_->GetStr()] = offset;
}

void ParameterDeclaration::Print(std::ostream &stream) const
{
    declaration_specifiers_->Print(stream);
    stream << " ";
    init_declarator_->Print(stream);
    stream << ", ";
}
