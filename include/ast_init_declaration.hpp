#ifndef AST_INIT_DECLARATION_HPP
#define AST_INIT_DECLARATION_HPP

#include "ast_node.hpp"
#include "ast_direct_declarator.hpp"
#include "ast_identifier.hpp"

class InitDeclaration : public Node
{
private:
    Identifier*                 declarator_;
    Node*                       initializer_;
public:
    InitDeclaration(Identifier* declarator ,Node* initializer) : declarator_(declarator), initializer_(initializer){};
    ~InitDeclaration() override
    {
        delete declarator_;
        delete initializer_;
    };
    virtual void EmitRISC(std::ostream &stream, Context &context) const override;
    virtual void Print(std::ostream &stream) const override;
    void InitTypeMap(Context &context, std::string type) const;
    void GlobalDeclaration(std::ostream &stream, Context &context) const;
};

#endif
