#include "ast_direct_declarator.hpp"

void DirectDeclarator::EmitRISC(std::ostream &stream, Context &context) const
{
    if (identifier_->IsFunction())
    {
        stream << identifier_->GetStr() << ":" << std::endl;
    }

}

void DirectDeclarator::Print(std::ostream &stream) const
{
    identifier_->Print(stream);
}
