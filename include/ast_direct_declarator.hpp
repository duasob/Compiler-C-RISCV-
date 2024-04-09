#ifndef AST_DIRECT_DECLARATOR_HPP
#define AST_DIRECT_DECLARATOR_HPP

#include "ast_identifier.hpp"
#include "ast_node.hpp"

class DirectDeclarator : public Node
{
private:
    Identifier *identifier_;


public:
    DirectDeclarator(Identifier *identifier) : identifier_(identifier){};
    ~DirectDeclarator()
    {
        delete identifier_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    virtual std::string GetStr() const { return identifier_->GetStr(); }
    virtual bool IsFunction() const { return identifier_->IsFunction(); }
};

#endif
