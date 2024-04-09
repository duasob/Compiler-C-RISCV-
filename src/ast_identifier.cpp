#include "ast_identifier.hpp"

void Identifier::EmitRISC(std::ostream &stream, Context &context) const
{

    if (isFunction_)
    {
        int startReg = context.opReg;
        if (parameter_list_ != nullptr)
        {
            parameter_list_->EmitRISC(stream, context);
        }

        if(context.currentScope->name != "function"){
            for (int i = 0; i < GetParamSize(); i++){
            stream << "mv a" << i << ", a" << startReg + i << std::endl;
            }
            stream << "call " << identifier_ << std::endl;
            stream << "mv a" << context.opReg << ", a0" << std::endl;
        }


    }
    else{
        int offset = context.Offset(identifier_, stream);
        std::string type = context.Type(identifier_, stream);
        if (offset != 0){
            if (context.ArrayType(identifier_) == "pointer"){
                if(context.storeLoad){
                    stream << "lw a" << context.opReg << ",-" << offset << "(s0)" <<std::endl;
                }else{
                    stream << "sw a" << context.opReg << ",-" << offset << "(s0)" <<std::endl;
                }
            }
            else if (type == "int"){
                stream << "lw    a" << context.opReg <<",-" << offset << "(s0)" <<std::endl;
                context.opType = "int";
            }
            else if (type == "float"){
                stream << "flw    fa" << context.opReg <<  ",-" << offset << "(s0)" <<std::endl;
                context.opType = "float";
            }
            else if (type == "double"){
                stream << "fld    fa" << context.opReg <<  ",-" << offset << "(s0)" <<std::endl;
                context.opType = "double";
            }
        }
    }
}


void Identifier::Print(std::ostream &stream) const
{
    stream << identifier_;
    if (isFunction_)
    {
        stream << "(";
        if (parameter_list_ != nullptr)
        {
            parameter_list_->Print(stream);
        }
        stream << ")";
    }

};


