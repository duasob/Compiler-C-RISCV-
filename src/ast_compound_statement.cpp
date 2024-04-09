#include "ast_compound_statement.hpp"



void CompoundStatement::EmitRISC(std::ostream &stream, Context &context) const
{

    Context::ScopeTree* current = context.currentScope;
    while (current->name == "compound" && current != nullptr){
        current = current->parent;

    }
    context.AddScopeTree("compound", current, stream);
    if (declarationList_ != nullptr)
    {
        declarationList_->EmitRISC(stream, context);
    }
    if (statementList_ != nullptr)
    {
        statementList_->EmitRISC(stream, context);
    }
    context.RemoveScopeTree();
}

void CompoundStatement::Print(std::ostream &stream) const
{
    stream << std::endl;
    stream << "{" << std::endl;
    if (declarationList_ != nullptr)
    {
        declarationList_->Print(stream);
    }
    if (statementList_ != nullptr)
    {
        statementList_->Print(stream);
    }
    stream << std::endl;
    stream << "}" << std::endl;

}
