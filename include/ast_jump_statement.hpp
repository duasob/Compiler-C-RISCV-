#ifndef AST_JUMP_STATEMENT_HPP
#define AST_JUMP_STATEMENT_HPP

#include "ast_node.hpp"
#include "ast.hpp"
class ReturnStatement : public Node
{
private:
    Expression *expression_;

public:
    ReturnStatement(Expression *expression) : expression_(expression) {}
    ~ReturnStatement()
    {
        delete expression_;
    };

    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
};

#endif
