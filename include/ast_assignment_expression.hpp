#ifndef AST_ASSIGNMENT_EXPRESSION_HPP
#define AST_ASSIGNMENT_EXPRESSION_HPP

#include "ast_node.hpp"
#include "ast_expression.hpp"

class AssignmentExpression : public Expression
{
private:
    Expression*                         identifier_;
    std::string                         assignment_operator_;
    Expression*                         assignment_expression_;

public:
    AssignmentExpression(Expression* identifier, std::string assignment_operator, Expression* assignment_expression ) : Expression(nullptr , false), identifier_(identifier), assignment_operator_(assignment_operator), assignment_expression_(assignment_expression){};
    ~AssignmentExpression(){
        delete identifier_;
        delete assignment_expression_;

    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
};


#endif
