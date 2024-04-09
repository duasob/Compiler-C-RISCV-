#include "ast_sizeof.hpp"



void SizeOf::EmitRISC(std::ostream &stream, Context &context) const
{
    //stream << "hey" << std::endl;
    if(identifier_ != ""){
        if (identifier_ == "int")
        {
            stream << "li a" << context.opReg << ", 4" << std::endl;
        }
        else if (identifier_ == "char")
        {
            stream << "li a" << context.opReg << ", 1" << std::endl;
        }
        else if (identifier_ == "void")
        {
            stream << "li a" << context.opReg << ", 0" << std::endl;
        }
        else if (identifier_ == "float")
        {
            stream << "li a" << context.opReg << ", 4" << std::endl;
        }
        else if (identifier_ == "double")
        {
            stream << "li a" << context.opReg << ", 8" << std::endl;
        }
        else
        {
           // just in case
            stream << "li a" << context.opReg << ", 4" << std::endl;
        }
    }else if (expression_!= nullptr){
         if(context.ArrayType(expression_->GetStr()) == "array" && (!expression_->IsArray())){
            stream << "li a" << context.opReg << "," << context.calculateSize(context.Type(expression_->GetStr()), true, context.ArraySize(expression_->GetStr())) << std::endl;
        }else if(context.ArrayType(expression_->GetStr()) == "pointer"){
            stream << "li a" << context.opReg << ", 4" << std::endl;
        }else {

            if(context.Type(expression_->GetStr())=="char"){
                stream << "li a" << context.opReg << ", 1" << std::endl;
            }else{
                stream << "li a" << context.opReg << "," <<  context.calculateSize(context.Type(expression_->GetStr()), false, 0)<< std::endl;
            }
        }
    }
}


void SizeOf::Print(std::ostream &stream) const
{
    stream << "sizeof() " << identifier_;
}



