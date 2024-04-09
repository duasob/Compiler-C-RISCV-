#ifndef AST_ARRAY_HPP
#define AST_ARRAY_HPP

#include "ast_node.hpp"
#include "ast_identifier.hpp"

class Array : public Identifier
{
private:
    std::string identifier_;
    int size_;
    Expression* expression_;

public:

    Array(std::string identifier, int size, Expression* expression) : Identifier("", false ,nullptr), identifier_(identifier), size_(size), expression_(expression){};
    ~Array(){
        delete expression_;
    };
    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    bool IsArray() const override { return true; }
    std::string GetStr() const override { return identifier_; }
    int GetParamSize() const override {return  size_;}

};


#endif
