#ifndef AST_EXPRESSION_OPERATIONS_HPP
#define AST_EXPRESSION_OPERATIONS_HPP

#include "ast_expression.hpp"

class ExpressionAdd : public Expression
{
private:
    Expression* left_;
    Expression* right_;

public:
    ExpressionAdd(Expression* left, Expression* right) : Expression(nullptr, false) , left_(left), right_(right){};
    ~ExpressionAdd()
    {
        delete left_;
        delete right_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    int GetValue() const override{
        return left_->GetValue() + right_->GetValue();
    };
};

class ExpressionMul : public Expression
{
private:
    Expression* left_;
    Expression* right_;

public:
    ExpressionMul(Expression* left, Expression* right) : Expression(nullptr, false) , left_(left), right_(right){};
    ~ExpressionMul()
    {
        delete left_;
        delete right_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    int GetValue() const override{
        return left_->GetValue() * right_->GetValue();
    };

};

class ExpressionBitOr : public Expression
{
private:
    Expression* left_;
    Expression* right_;

public:
    ExpressionBitOr(Expression* left, Expression* right) : Expression(nullptr, false) , left_(left), right_(right){};
    ~ExpressionBitOr()
    {
        delete left_;
        delete right_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    int GetValue() const override{
        return left_->GetValue() | right_->GetValue();
    };

};

class ExpressionBitAnd : public Expression
{
private:
    Expression* left_;
    Expression* right_;

public:
    ExpressionBitAnd(Expression* left, Expression* right) : Expression(nullptr, false) , left_(left), right_(right){};
    ~ExpressionBitAnd()
    {
        delete left_;
        delete right_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    int GetValue() const override{
        return left_->GetValue() & right_->GetValue();
    };

};

class ExpressionBitXor : public Expression
{
private:
    Expression* left_;
    Expression* right_;

public:
    ExpressionBitXor(Expression* left, Expression* right) : Expression(nullptr, false) , left_(left), right_(right){};
    ~ExpressionBitXor()
    {
        delete left_;
        delete right_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    int GetValue() const override{
        return left_->GetValue() ^ right_->GetValue();
    };

};

class ExpressionLessThan : public Expression
{
private:
    Expression* left_;
    Expression* right_;

public:
    ExpressionLessThan(Expression* left, Expression* right) : Expression(nullptr, false) , left_(left), right_(right){};
    ~ExpressionLessThan()
    {
        delete left_;
        delete right_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    int GetValue() const override{
        return left_->GetValue() < right_->GetValue();
    };

};

class ExpressionGreaterThan : public Expression
{
private:
    Expression* left_;
    Expression* right_;

public:
    ExpressionGreaterThan(Expression* left, Expression* right) : Expression(nullptr, false) , left_(left), right_(right){};
    ~ExpressionGreaterThan()
    {
        delete left_;
        delete right_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    int GetValue() const override{
        return left_->GetValue() > right_->GetValue();
    };

};

class ExpressionLessEqual : public Expression
{
private:
    Expression* left_;
    Expression* right_;

public:

    ExpressionLessEqual(Expression* left, Expression* right) : Expression(nullptr, false) , left_(left), right_(right){};
    ~ExpressionLessEqual()
    {
        delete left_;
        delete right_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    int GetValue() const override{
        return left_->GetValue() <= right_->GetValue();
    };

};

class ExpressionGreaterEqual : public Expression
{
private:
    Expression* left_;
    Expression* right_;

public:
    ExpressionGreaterEqual(Expression* left, Expression* right) : Expression(nullptr, false) , left_(left), right_(right){};
    ~ExpressionGreaterEqual()
    {
        delete left_;
        delete right_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    int GetValue() const override{
        return left_->GetValue() >= right_->GetValue();
    };

};

class ExpressionDiv : public Expression
{
private:
    Expression* left_;
    Expression* right_;

public:
    ExpressionDiv(Expression* left, Expression* right) : Expression(nullptr, false) , left_(left), right_(right){};
    ~ExpressionDiv()
    {
        delete left_;
        delete right_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    int GetValue() const override{
        return left_->GetValue() / right_->GetValue();
    };

};

class ExpressionSub : public Expression
{
private:
    Expression* left_;
    Expression* right_;

public:

    ExpressionSub(Expression* left, Expression* right) : Expression(nullptr, false) , left_(left), right_(right){};
    ~ExpressionSub()
    {
        delete left_;
        delete right_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    int GetValue() const override{
        return left_->GetValue() - right_->GetValue();
    };

};

class ExpressionEqual : public Expression
{
private:
    Expression* left_;
    Expression* right_;

public:
    ExpressionEqual(Expression* left, Expression* right) : Expression(nullptr, false) , left_(left), right_(right){};
    ~ExpressionEqual()
    {
        delete left_;
        delete right_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    int GetValue() const override{
        return left_->GetValue() == right_->GetValue();
    };
};

class ExpressionLogicalAnd : public Expression
{
private:
    Expression* left_;
    Expression* right_;

public:
    ExpressionLogicalAnd(Expression* left, Expression* right) : Expression(nullptr, false) , left_(left), right_(right){};
    ~ExpressionLogicalAnd()
    {
        delete left_;
        delete right_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    int GetValue() const override{
        return left_->GetValue() && right_->GetValue();
    };
};

class ExpressionLogicalOr : public Expression
{
private:
    Expression* left_;
    Expression* right_;

public:
    ExpressionLogicalOr(Expression* left, Expression* right) : Expression(nullptr, false) , left_(left), right_(right){};
    ~ExpressionLogicalOr()
    {
        delete left_;
        delete right_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    int GetValue() const override{
        return left_->GetValue() || right_->GetValue();
    };
};

class ExpressionMod : public Expression
{
private:
    Expression* left_;
    Expression* right_;

public:
    ExpressionMod(Expression* left, Expression* right) : Expression(nullptr, false) , left_(left), right_(right){};
    ~ExpressionMod()
    {
        delete left_;
        delete right_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    int GetValue() const override{
        return left_->GetValue() % right_->GetValue();
    };
};

class ExpressionLeftShift : public Expression
{
private:
    Expression *left_;
    Expression *right_;

public:
    ExpressionLeftShift(Expression *left, Expression *right) : Expression(nullptr, false), left_(left), right_(right){};
    ~ExpressionLeftShift()
    {
        delete left_;
        delete right_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    int GetValue() const override{
        return left_->GetValue() << right_->GetValue();
    };
};

class ExpressionRightShift : public Expression
{
private:
    Expression *left_;
    Expression *right_;

public:
    ExpressionRightShift(Expression *left, Expression *right) : Expression(nullptr, false), left_(left), right_(right){};
    ~ExpressionRightShift()
    {
        delete left_;
        delete right_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    int GetValue() const override{
        return left_->GetValue() >> right_->GetValue();
    };
};

class ExpressionNotEqual : public Expression
{
private:
    Expression *left_;
    Expression *right_;

public:
    ExpressionNotEqual(Expression *left, Expression *right) : Expression(nullptr, false), left_(left), right_(right){};
    ~ExpressionNotEqual()
    {
        delete left_;
        delete right_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    int  GetValue() const override{
        return left_->GetValue() != right_->GetValue();
    };
};
class ExpressionConditional : public Expression
{
private:
    Expression *condition_;
    Expression *trueExpression_;
    Expression *falseExpression_;

public:
    ExpressionConditional(Expression *condition, Expression *trueExpression, Expression *falseExpression) : Expression(nullptr, false), condition_(condition), trueExpression_(trueExpression), falseExpression_(falseExpression){};
    ~ExpressionConditional()
    {
        delete condition_;
        delete trueExpression_;
        delete falseExpression_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    int GetValue() const override{
        return condition_->GetValue() ? trueExpression_->GetValue() : falseExpression_->GetValue();
    };
};

class ExpressionPostInc : public Expression
{
private:
    Expression *expression_;

public:
    ExpressionPostInc(Expression *expression) : Expression(nullptr, false), expression_(expression){};
    ~ExpressionPostInc()
    {
        delete expression_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
};

class ExpressionPostDec : public Expression
{
private:
    Expression *expression_;

public:
    ExpressionPostDec(Expression *expression) : Expression(nullptr, false), expression_(expression){};
    ~ExpressionPostDec()
    {
        delete expression_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;

};

class ExpressionPreInc : public Expression
{
private:
    Expression *expression_;

public:
    ExpressionPreInc(Expression *expression) : Expression(nullptr, false), expression_(expression){};
    ~ExpressionPreInc()
    {
        delete expression_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;

};

class ExpressionPreDec : public Expression
{
private:
    Expression *expression_;

public:
    ExpressionPreDec(Expression *expression) : Expression(nullptr, false), expression_(expression){};
    ~ExpressionPreDec()
    {
        delete expression_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;

};

#endif
