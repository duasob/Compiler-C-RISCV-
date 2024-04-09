#include "ast_unary.hpp"

void Unary::EmitRISC(std::ostream &stream, Context &context) const {
    if (unary_operator_ == "-") {
        expression_->EmitRISC(stream, context);
        stream << "neg a" << context.opReg << ",a" << context.opReg <<  std::endl;
    } else if (unary_operator_ == "!") {
        expression_->EmitRISC(stream, context);
        stream << "seqz a" << context.opReg << ",a" << context.opReg << std::endl;
        stream << "andi a" << context.opReg << ",a" << context.opReg << ",0xff" << std::endl;
    } else if (unary_operator_ == "~") {
        expression_->EmitRISC(stream, context);
        stream << "not a" << context.opReg << ",a" << context.opReg << std::endl;
    } else if (unary_operator_ == "&") {
        expression_->EmitRISC(stream, context);
        stream << "addi a" << context.opReg << ",s0,-" << context.Offset(expression_->GetStr()) << std::endl;
    } else if (unary_operator_ == "*") {
        if(context.storeLoad){
            context.opReg++;
            expression_->EmitRISC(stream, context);
            stream << "lw a" << context.opReg << ",0(a" << context.opReg << ")" << std::endl;
        }else{
            context.opReg++;
            context.storeLoad = 1;
            expression_->EmitRISC(stream, context);
            context.storeLoad = 0;
            stream << "sw a" << context.opReg - 1<< ",0(a" << context.opReg   << ")" << std::endl;
        }
    }
}

void Unary::Print(std::ostream &stream) const
{
    expression_->Print(stream);
}
