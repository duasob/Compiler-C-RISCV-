#include "ast_init_declaration_list.hpp"

void InitDeclarationList::EmitRISC(std::ostream &stream, Context &context) const
{
    for (auto node : init_declaration_list_)
    {
        if (node == nullptr)
        {
            continue;
        }
        node->EmitRISC(stream, context);
    }
}

void InitDeclarationList::Print(std::ostream &stream) const
{

    for (auto node : init_declaration_list_)
    {
        if (node == nullptr)
        {
            continue;
        }
        node->Print(stream);

    }

}
