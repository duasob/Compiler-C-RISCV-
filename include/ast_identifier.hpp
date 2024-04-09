#ifndef AST_IDENTIFIER_HPP
#define AST_IDENTIFIER_HPP

#include "ast_node.hpp"
#include "ast_expression.hpp"

class Identifier : public Expression
{
private:
    std::string identifier_;
    NodeList* parameter_list_;
    bool isFunction_;

public:


    Identifier(std::string identifier, bool isFunction, NodeList* parameter_list) : Expression(this ,isFunction), identifier_(identifier), parameter_list_(parameter_list){
            isFunction_ = isFunction;

    };
    ~Identifier(){
        delete parameter_list_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    std::string GetStr() const override { return identifier_; }
    bool IsFunction() const override { return isFunction_; }
    bool IsArray() const override { return false; }
    int GetParamSize() const override {return parameter_list_ == nullptr ?  0 :  parameter_list_->GetSize();}
    Identifier* ChangeIsFunction(bool isFunction, NodeList* parameter_list = nullptr) override {isFunction_ = isFunction; parameter_list_ = parameter_list; return this;}

};


#endif
