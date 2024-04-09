#ifndef AST_CONSTANT_HPP
#define AST_CONSTANT_HPP

#include "ast_node.hpp"
#include "ast_expression.hpp"
class IntConstant : public Expression
{
private:
    int value_;

public:
    IntConstant(int value) : Expression(this, false), value_(value) {}

    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    int GetValue() const override { return value_; }
};


class FloatConstant : public Expression
{
private:
    float value_;

public:
    FloatConstant(float value) : Expression(this, false), value_(value) {}

    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
};

class CharConstant : public Expression
{
    private:
        int value_;
    public:
        CharConstant(std::string value) : Expression(this, false),  value_(int(value[1]))  {}

        void EmitRISC(std::ostream &stream, Context &context) const override;
        void Print(std::ostream &stream) const override;
        int GetValue() const { return value_; }

};

class StringConstant : public Expression
{
    private:
        std::string value_;
    public:
        StringConstant(std::string value) : Expression(this, false),  value_(value)  {}

        void EmitRISC(std::ostream &stream, Context &context) const override;
        void Print(std::ostream &stream) const override;

};


#endif
