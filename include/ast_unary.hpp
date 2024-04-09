#ifndef AST_UNARY_HPP
#define AST_UNARY_HPP

#include "ast_node.hpp"
#include "ast_expression.hpp"
class Unary : public Expression
{
private:
    std::string unary_operator_;
    Expression* expression_;

public:
    Unary(std::string unary_operator, Expression* expression) : Expression(this, false), unary_operator_(unary_operator), expression_(expression) {}
    ~Unary(){
        delete expression_;
    }
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    std::string GetStr() const override { return expression_->GetStr(); }
};

#endif




