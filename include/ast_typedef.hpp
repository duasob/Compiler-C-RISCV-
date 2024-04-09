#ifndef AST_TYPEDEF_HPP
#define AST_TYPEDEF_HPP

#include "ast_node.hpp"
#include "ast_type_specifier.hpp"

class Typedef : public TypeSpecifier
{
private:
    std::string type_;
    TypeSpecifier* declaration_specifiers_;

public:
    Typedef(std::string type, TypeSpecifier* declaration_specifiers) : TypeSpecifier(""), type_(type), declaration_specifiers_(declaration_specifiers){};
    ~Typedef(){
        delete declaration_specifiers_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    std::string GetStr() const  { return type_; }
};

#endif
