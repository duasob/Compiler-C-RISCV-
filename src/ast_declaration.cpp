#include "ast_declaration.hpp"

void Declaration::EmitRISC(std::ostream &stream, Context &context) const
{


    init_declarator_->InitTypeMap(context, declaration_specifiers_->GetStr());
    context.opReg += 1;
    init_declarator_->EmitRISC(stream, context);
    context.opReg -= 1;


}

void Declaration::Print(std::ostream &stream) const
{

    declaration_specifiers_->Print(stream);
    stream << " ";
    init_declarator_->Print(stream);
}
