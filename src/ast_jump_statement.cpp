#include "ast_jump_statement.hpp"

void ReturnStatement::EmitRISC(std::ostream &stream, Context &context) const
{
    if(expression_->IsFunction()){

        context.storeLoad = 1;
        expression_->EmitRISC(stream, context);
        context.storeLoad = 0;

    }else if (expression_ != nullptr)
    {
        context.opReg += 1;
        context.storeLoad = 1;
        expression_->EmitRISC(stream, context);
        context.storeLoad = 0;
        std::string type = context.functionType.back();
        if (type == "int")
        {
            stream << "mv a0, a" << context.opReg << std::endl;
        }
        else if (type == "float")
        {
            stream << "fmv.s fa0, fa" << context.opReg << std::endl;
        }
        else if (type == "double")
        {
            stream << "fmv.d fa0, fa" << context.opReg << std::endl;
        } else if (type == "unsigned"){
            stream << "mv a0, a" << context.opReg << std::endl;
        }
        context.opReg -= 1;
    }



    stream << "lw ra, " << context.stackSize.back() - 4 << "(sp)" << std::endl;
    stream << "lw " << " s0, " << context.stackSize.back() - 8 << "(sp)" << std::endl;
    stream << "lw " << " s1, " << context.stackSize.back() - 12 << "(sp)" << std::endl;
    stream << "addi sp, sp, " << context.stackSize.back() << std::endl;
    stream << "jr ra" << std::endl;
}

void ReturnStatement::Print(std::ostream &stream) const
{
    stream << "return";
    if (expression_ != nullptr)
    {
        stream << " ";
        expression_->Print(stream);
    }
    if(expression_->isFunction_)
    {
        stream << "()";
    }
    stream << ";" << std::endl;
}
