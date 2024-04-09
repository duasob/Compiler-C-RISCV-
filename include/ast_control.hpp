#ifndef AST_CONTROL_HPP
#define AST_CONTROL_HPP

#include "ast_expression.hpp"

class ControlIfElse : public Expression
{
private:
    Expression* ifCondition_;
    Node* ifStatement_;
    Node* elseStatement_;


public:
    ControlIfElse(Expression* ifCondition, Node* ifStatement,  Node* elseStatement) : Expression(nullptr, false) , ifCondition_(ifCondition),ifStatement_(ifStatement), elseStatement_(elseStatement){};
    ~ControlIfElse()
    {
        delete ifCondition_;
        delete ifStatement_;
        delete elseStatement_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;

};

class ControlWhile : public Expression
{
private:
    Expression* whileCondition_;
    Node* whileStatement_;
    bool isDoWhile_;

public:
    ControlWhile(Expression* whileCondition, Node* whileStatement, bool isDoWhile) : Expression(nullptr, false) , whileCondition_(whileCondition),whileStatement_(whileStatement), isDoWhile_(isDoWhile){};
    ~ControlWhile()
    {
        delete whileCondition_;
        delete whileStatement_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;

};

class ControlFor : public Expression
{
private:
    Expression* forInit_;
    Expression* forCondition_;
    Expression* forIncrement_;
    Node* forStatement_;

public:
    ControlFor(Expression* forInit, Expression* forCondition, Expression* forIncrement,  Node* forStatement) : Expression(nullptr, false) , forInit_(forInit), forCondition_(forCondition),forIncrement_(forIncrement), forStatement_(forStatement){};
    ~ControlFor()
    {
        delete forInit_;
        delete forCondition_;
        delete forIncrement_;
        delete forStatement_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;

};
class ControlSwitch : public Expression
{
private:
    Expression* expression_;
    Node* statement_;

public:
    ControlSwitch(Expression* expression,  Node* statement) : Expression(nullptr, false) , expression_(expression), statement_(statement){};
    ~ControlSwitch()
    {
      delete expression_;
      delete statement_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;

};

class ControlCase : public Expression
{
private:
    Expression* expression_;
    Node* statement_;

public:
    ControlCase(Expression* expression,  Node* statement) : Expression(nullptr, false) , expression_(expression), statement_(statement){};
    ~ControlCase()
    {
      delete expression_;
      delete statement_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    Expression* GetExpression() const {return expression_;};

};

class ControlBreak : public Expression
{
public:
    ControlBreak() : Expression(nullptr, false){};
    ~ControlBreak(){};
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;

};

#endif
