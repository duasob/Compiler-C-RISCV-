#ifndef AST_POINTER_HPP
#define AST_POINTER_HPP


#include "ast_identifier.hpp"
#include "ast_expression.hpp"

class Pointer : public Identifier
{
private:
    std::string identifier_;
    Expression* index_;

public:

    Pointer(std::string identifier, Expression* index) : Identifier("", false ,nullptr), identifier_(identifier), index_(index){};
    ~Pointer(){
        delete index_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    bool IsPointer() const override { return true; }
    std::string GetStr() const override { return identifier_; }

};

#endif
