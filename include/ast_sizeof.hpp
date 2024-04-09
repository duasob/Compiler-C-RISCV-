#ifndef AST_SIZEOFF_HPP
#define AST_SIZEOFF_HPP


#include "ast_identifier.hpp"
#include "ast_expression.hpp"

class SizeOf : public Expression
{
private:
    std::string identifier_;
    Expression* expression_;


public:

    SizeOf(std::string identifier, Expression* expression) : Expression(nullptr, false), identifier_(identifier), expression_(expression){};
    ~SizeOf(){
        delete expression_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
};

#endif
