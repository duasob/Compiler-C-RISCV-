#ifndef AST_INIT_DECLARATION_LIST_HPP
#define AST_INIT_DECLARATION_LIST_HPP

#include "ast_node.hpp"
#include "ast_init_declaration.hpp"

class InitDeclarationList : public NodeList
{
private:
    std::vector<InitDeclaration*>                 init_declaration_list_;
public:
    InitDeclarationList( InitDeclaration* init_declaration) : NodeList(nullptr), init_declaration_list_({init_declaration}){};
    ~InitDeclarationList() override
    {
        for (auto &init_declaration : init_declaration_list_)
        {
            delete init_declaration;
        }
    };
    virtual void EmitRISC(std::ostream &stream, Context &context) const override;
    virtual void Print(std::ostream &stream) const override;
    void PushBack(InitDeclaration* item) { init_declaration_list_.push_back(item); }
    void InitTypeMap(Context &context, std::string type) const {
        for (auto &init_declaration : init_declaration_list_){
            init_declaration->InitTypeMap(context, type);
        }
    };
};

#endif
