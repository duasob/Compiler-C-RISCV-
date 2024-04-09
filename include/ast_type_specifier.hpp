#ifndef AST_TYPE_SPECIFIER_HPP
#define AST_TYPE_SPECIFIER_HPP

#include "ast_node.hpp"

class TypeSpecifier : public Node
{
private:
    std::string type_;

public:
    TypeSpecifier(std::string type) : type_(type){};
    ~TypeSpecifier(){};
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    std::string GetStr() const  { return type_; }
};

#endif
