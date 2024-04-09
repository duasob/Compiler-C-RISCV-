#ifndef AST_DECLARATION_HPP
#define AST_DECLARATION_HPP

#include "ast.hpp"
#include "ast_node.hpp"
#include "ast_init_declaration_list.hpp"

class Declaration : public Node
{
private:
    TypeSpecifier*                  declaration_specifiers_;
    InitDeclarationList*               init_declarator_;

public:
    Declaration(TypeSpecifier* declaration_specifiers, InitDeclarationList *init_declarator) : declaration_specifiers_(declaration_specifiers),  init_declarator_(init_declarator) {};

    ~Declaration()
    {
        delete declaration_specifiers_;
        delete init_declarator_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;


};

#endif
