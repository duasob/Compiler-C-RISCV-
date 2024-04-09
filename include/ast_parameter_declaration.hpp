#ifndef AST_PARAMETER_DECLARATION_HPP
#define AST_PARAMETER_DECLARATION_HPP

#include "ast.hpp"
#include "ast_node.hpp"

class ParameterDeclaration : public Node
{
private:
    TypeSpecifier*                        declaration_specifiers_;
    Identifier*                           init_declarator_;

public:
    ParameterDeclaration(TypeSpecifier* declaration_specifiers, Identifier *init_declarator) : declaration_specifiers_(declaration_specifiers),  init_declarator_(init_declarator) {};

    ~ParameterDeclaration()
    {
        delete declaration_specifiers_;
        delete init_declarator_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;


};

#endif

