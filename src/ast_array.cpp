#include "ast_array.hpp"



void Array::EmitRISC(std::ostream &stream, Context &context) const
{
    context.opReg++;
    expression_->EmitRISC(stream, context);

    std::string type = context.Type(identifier_);
    std::string arrayType = context.ArrayType(identifier_);

    if (arrayType == "pointer"){
        if (type == "int"){
            stream << "slli a" << context.opReg << ", a" << context.opReg << ", 2" << std::endl;
            stream << "lw a" << context.opReg +1 << ",-" << context.Offset(identifier_)  <<"(s0)"<< std::endl;
            stream << "add a" << context.opReg  << ", a" << context.opReg +1 << ", a"<< context.opReg << std::endl;
            if(context.storeLoad){
                stream << "lw a" << context.opReg -1 << ", 0(a"<< context.opReg << ")"<< std::endl;
            }else{
                stream << "sw a" << context.opReg -2 << ", 0(a"<< context.opReg << ")"<< std::endl;
            }
        }else if (type == "char"){
            stream << "lw a" << context.opReg +1  << ",-" << context.Offset(identifier_) <<"(s0)"<< std::endl;
            stream << "add a" << context.opReg  << ", a" << context.opReg +1 << ", a"<< context.opReg << std::endl;
            if(context.storeLoad){
                stream << "lbu a" << context.opReg  << ", 0(a"<< context.opReg << ")"<< std::endl;
                context.opReg++;
            }else{
                stream << "sw a" << context.opReg -2 << ", 0(a"<< context.opReg << ")"<< std::endl;
            }
        }

    }else if (type == "int" || type == "float")
    {
        stream << "slli a" << context.opReg << ", a" << context.opReg << ", 2" << std::endl;
        stream << "li a" << context.opReg +1 << ", " << context.Offset(identifier_)<< std::endl;
        stream << "sub a" << context.opReg  << ", a" << context.opReg +1 << ", a"<< context.opReg << std::endl;
        stream << "sub a" << context.opReg  << ", " << "s0, a" << context.opReg   << std::endl;
        if(context.storeLoad){
            stream << "lw a" << context.opReg -1 << ", 0(a"<< context.opReg << ")"<< std::endl;
        }else{
            stream << "sw a" << context.opReg -2 << ", 0(a"<< context.opReg << ")"<< std::endl;
        }

    }
    else if (type == "char")
    {

    }
    else if (type == "double")
    {
        stream << "slli a" << context.opReg << ", a" << context.opReg << ", 3" << std::endl;
    }


    context.opReg--;

}

void Array::Print(std::ostream &stream) const
{
    stream << "Array: " << identifier_ << "[" << size_ << "]";
}



