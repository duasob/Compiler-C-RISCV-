#ifndef AST_COMPOUND_STATEMENT_HPP
#define AST_COMPOUND_STATEMENT_HPP

#include "ast_declaration.hpp"
#include "ast_node.hpp"

class CompoundStatement : public Node
{
private:
    NodeList*               declarationList_;
    NodeList*               statementList_;
public:
    CompoundStatement(NodeList* declarationList ,NodeList* statementList) : declarationList_(declarationList), statementList_(statementList){};
    ~CompoundStatement() override
    {
        delete declarationList_;
        delete statementList_;
    };
    virtual void EmitRISC(std::ostream &stream, Context &context) const override;
    virtual void Print(std::ostream &stream) const override;
};

#endif
