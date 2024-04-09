#ifndef AST_EXPRESSION_HPP
#define AST_EXPRESSION_HPP

#include "ast_node.hpp"

class Expression : public Node
{
private:
    Expression *expression_;

public:
    bool isFunction_;

    Expression(Expression *expression, bool isFunction) : expression_(expression), isFunction_(isFunction){};
    ~Expression()
    {
        delete expression_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    virtual std::string GetStr() const { return ""; }
    virtual Expression* ChangeIsFunction(bool isFunction, NodeList* parameter_list = nullptr) {isFunction_ = isFunction; return this;}
    virtual bool IsFunction() const { return isFunction_; }
    virtual bool IsArray() const { return false; }
    virtual bool IsPointer() const { return false; }
    virtual int GetParamSize() const {return 0;}
    virtual int GetValue() const {return 0;}
};



#endif
