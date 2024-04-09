#include "ast_assignment_expression.hpp"



void AssignmentExpression::EmitRISC(std::ostream &stream, Context &context) const
{
    if (assignment_operator_ == "="){
        context.storeLoad = 1;
        assignment_expression_->EmitRISC(stream, context);
        context.storeLoad = 0;
        //stream << identifier_->GetStr() << context.ArrayType(identifier_->GetStr())<<identifier_->IsArray() << std::endl;
        if(identifier_->IsArray()){
            context.opReg++;
            context.storeLoad = 0;
            identifier_->EmitRISC(stream, context);
            context.opReg--;
        }else {
            if (context.ArrayType(identifier_->GetStr()) == "pointer"){
            //stream << "here" << std::endl;
            context.storeLoad = 0;
            //stream << context.storeLoad<< std::endl;
            identifier_->EmitRISC(stream, context);

            }else{
                //stream << context.Type(identifier_->GetStr()) << std::endl;
                if(context.Type(identifier_->GetStr()) == "int"){
                    stream << "sw a"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                }else if (context.Type(identifier_->GetStr()) == "float"){
                    stream << "fsw fa"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                }else if (context.Type(identifier_->GetStr()) == "double"){
                    stream << "fsd fa"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                }else{
                    // TODO: unsigned
                    //stream << " bad here" << std::endl;
                }
            }
        }
    }else if(assignment_operator_ == "+="){
    context.storeLoad = 1;
        assignment_expression_->EmitRISC(stream, context);
        context.storeLoad = 0;
        if(identifier_->IsArray()){
            context.opReg++;
            context.storeLoad = 0;
            identifier_->EmitRISC(stream, context);
            context.opReg--;
        }else{
            if(context.Type(identifier_->GetStr()) == "int"){
                stream << "lw a" << context.opReg + 1 << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                stream << "add a" << context.opReg << ",a" << context.opReg << ",a" << context.opReg + 1 << std::endl;
                stream << "sw a"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;

            }else if (context.Type(identifier_->GetStr()) == "float"){
                stream << "flw fa" << context.opReg + 1 << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                stream << "fadd.s fa" << context.opReg << ", fa"<< context.opReg << ", fa" << context.opReg + 1 << std::endl;
                stream << "fsw fa"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
            }else if (context.Type(identifier_->GetStr()) == "double"){
                stream << "fld fa" << context.opReg + 1 << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                stream << "fadd.d fa" << context.opReg << ", fa"<< context.opReg << ", fa" << context.opReg + 1 << std::endl;
                stream << "fsd fa"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
            }else{
                context.storeLoad = 0;
                identifier_->EmitRISC(stream, context);
            }
        }
        context.opReg-=2;
        }else if(assignment_operator_ == "-="){
            context.storeLoad = 1;
            assignment_expression_->EmitRISC(stream, context);
            context.storeLoad = 0;
            if(identifier_->IsArray()){
                context.opReg++;
                context.storeLoad = 0;
                identifier_->EmitRISC(stream, context);
                context.opReg--;
            }else{
                if(context.Type(identifier_->GetStr()) == "int"){
                    stream << "lw a" << context.opReg + 1 << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                    stream << "sub a" << context.opReg << ",a" << context.opReg + 1 << ",a" << context.opReg << std::endl;
                    stream << "sw a"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;

                }else if (context.Type(identifier_->GetStr()) == "float"){
                    stream << "flw fa" << context.opReg + 1 << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                    stream << "fsub.s fa" << context.opReg << ", fa"<< context.opReg + 1 << ", fa" << context.opReg << std::endl;
                    stream << "fsw fa"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                }else if (context.Type(identifier_->GetStr()) == "double"){
                    stream << "fld fa" << context.opReg + 1 << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                    stream << "fsub.d fa" << context.opReg << ", fa"<< context.opReg + 1 << ", fa" << context.opReg << std::endl;
                    stream << "fsd fa"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                }else{
                    // unary operator for example
                    context.storeLoad = 0;
                    identifier_->EmitRISC(stream, context);
                }
            }
            context.opReg-=2;
        }else if (assignment_operator_ == ">>="){
            context.storeLoad = 1;
            assignment_expression_->EmitRISC(stream, context);
            context.storeLoad = 0;
            if(identifier_->IsArray()){
                context.opReg++;
                context.storeLoad = 0;
                identifier_->EmitRISC(stream, context);
                context.opReg--;
            }else {

                if(context.Type(identifier_->GetStr()) == "int"){
                    stream << "lw a" << context.opReg + 1 << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                    stream << "sra a" << context.opReg << ",a" << context.opReg + 1 << ",a" << context.opReg << std::endl;
                    stream << "sw a"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;

                }else if (context.Type(identifier_->GetStr()) == "float"){
                    stream << "fsw fa"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                }else if (context.Type(identifier_->GetStr()) == "double"){
                    stream << "fsd fa"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                }else{
                    // unary operator for example
                    context.storeLoad = 0;
                    identifier_->EmitRISC(stream, context);
                }
            }
            context.opReg-=1;
        }else if (assignment_operator_ == "<<="){
            context.storeLoad = 1;
            assignment_expression_->EmitRISC(stream, context);
            context.storeLoad = 0;
            if(identifier_->IsArray()){
                context.opReg++;
                context.storeLoad = 0;
                identifier_->EmitRISC(stream, context);
                context.opReg--;
            }else {

                if(context.Type(identifier_->GetStr()) == "int"){
                    stream << "lw a" << context.opReg + 1 << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                    stream << "sll a" << context.opReg << ",a" << context.opReg + 1 << ",a" << context.opReg << std::endl;
                    stream << "sw a"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;

                }else if (context.Type(identifier_->GetStr()) == "float"){
                    stream << "fsw fa"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                }else if (context.Type(identifier_->GetStr()) == "double"){
                    stream << "fsd fa"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                }else{

                    context.storeLoad = 0;
                    identifier_->EmitRISC(stream, context);
                }
            }
            context.opReg-=1;
        }else if(assignment_operator_ == "<="){
            context.storeLoad = 1;
            assignment_expression_->EmitRISC(stream, context);
            context.storeLoad = 0;
            if(identifier_->IsArray()){
                context.opReg++;
                context.storeLoad = 0;
                identifier_->EmitRISC(stream, context);
                context.opReg--;
            }else{
                if(context.Type(identifier_->GetStr()) == "int"){
                    stream << "lw a" << context.opReg + 1 << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                    stream << "slt a" << context.opReg << ",a" << context.opReg + 1 << ",a" << context.opReg << std::endl;
                    stream << "sw a"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;

                }else if (context.Type(identifier_->GetStr()) == "float"){
                    stream << "flw fa"<< context.opReg + 1 << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                    stream << "flt.s fa"<< context.opReg << ",fa" << context.opReg + 1 << ",fa" << context.opReg << std::endl;
                    stream << "fsw fa"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                }else if (context.Type(identifier_->GetStr()) == "double"){
                    stream << "fld fa"<< context.opReg + 1 << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                    stream << "flt.d fa"<< context.opReg << ",fa" << context.opReg + 1 << ",fa" << context.opReg << std::endl;
                    stream << "fsd fa"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                }else{

                    context.storeLoad = 0;
                    identifier_->EmitRISC(stream, context);
                }
            }
            context.opReg-=1;
        } else if(assignment_operator_ == ">="){
            context.storeLoad = 1;
            assignment_expression_->EmitRISC(stream, context);
            context.storeLoad = 0;
            if(identifier_->IsArray()){
                context.opReg++;
                context.storeLoad = 0;
                identifier_->EmitRISC(stream, context);
                context.opReg--;
            }else{

                if(context.Type(identifier_->GetStr()) == "int"){
                    stream << "lw a" << context.opReg + 1 << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                    stream << "sgt a" << context.opReg << ",a" << context.opReg + 1 << ",a" << context.opReg << std::endl;
                    stream << "sw a"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;

                }else if (context.Type(identifier_->GetStr()) == "float"){
                    stream << "flw fa"<< context.opReg + 1 << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                    stream << "fsgt.s fa"<< context.opReg << ",fa" << context.opReg + 1 << ",fa" << context.opReg << std::endl;
                    stream << "fsw fa"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                }else if (context.Type(identifier_->GetStr()) == "double"){
                    stream << "fld fa"<< context.opReg + 1 << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                    stream << "fsgt.d fa"<< context.opReg << ",fa" << context.opReg + 1 << ",fa" << context.opReg << std::endl;
                    stream << "fsd fa"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                }else{

                    context.storeLoad = 0;
                    identifier_->EmitRISC(stream, context);
                }
            }
            context.opReg-=1;
        }else if(assignment_operator_ == "&="){
            context.storeLoad = 1;
            assignment_expression_->EmitRISC(stream, context);
            context.storeLoad = 0;
            if(identifier_->IsArray()){
                context.opReg++;
                context.storeLoad = 0;
                identifier_->EmitRISC(stream, context);
                context.opReg--;
            }else{

                if(context.Type(identifier_->GetStr()) == "int"){
                    stream << "lw a" << context.opReg + 1 << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                    stream << "and a" << context.opReg << ",a" << context.opReg + 1 << ",a" << context.opReg << std::endl;
                    stream << "sw a"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;

                    context.storeLoad = 0;
                    identifier_->EmitRISC(stream, context);
                }
            }
            context.opReg-=1;
        }else if(assignment_operator_ == "^="){
            context.storeLoad = 1;
            assignment_expression_->EmitRISC(stream, context);
            context.storeLoad = 0;
            if(identifier_->IsArray()){
                context.opReg++;
                context.storeLoad = 0;
                identifier_->EmitRISC(stream, context);
                context.opReg--;
            }else{

                if(context.Type(identifier_->GetStr()) == "int"){
                    stream << "lw a" << context.opReg + 1 << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                    stream << "xor a" << context.opReg << ",a" << context.opReg + 1 << ",a" << context.opReg << std::endl;
                    stream << "sw a"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;


                }else{

                    context.storeLoad = 0;
                    identifier_->EmitRISC(stream, context);
                }
            }
            context.opReg-=1;
        }else if(assignment_operator_ == "|="){
            context.storeLoad = 1;
            assignment_expression_->EmitRISC(stream, context);
            context.storeLoad = 0;
            if(identifier_->IsArray()){
                context.opReg++;
                context.storeLoad = 0;
                identifier_->EmitRISC(stream, context);
                context.opReg--;
            }else{

                if(context.Type(identifier_->GetStr()) == "int"){
                    stream << "lw a" << context.opReg + 1 << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                    stream << "or a" << context.opReg << ",a" << context.opReg + 1 << ",a" << context.opReg << std::endl;
                    stream << "sw a"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;


                }else{

                    context.storeLoad = 0;
                    identifier_->EmitRISC(stream, context);
                }
            }
            context.opReg-=1;
        }else if(assignment_operator_ == "*="){
            context.storeLoad = 1;
            assignment_expression_->EmitRISC(stream, context);
            context.storeLoad = 0;
            if(identifier_->IsArray()){
                context.opReg++;
                context.storeLoad = 0;
                identifier_->EmitRISC(stream, context);
                context.opReg--;
            }else{

                if(context.Type(identifier_->GetStr()) == "int"){
                    stream << "lw a" << context.opReg + 1 << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                    stream << "mul a" << context.opReg << ",a" << context.opReg + 1 << ",a" << context.opReg << std::endl;
                    stream << "sw a"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;

                }else if (context.Type(identifier_->GetStr()) == "float"){
                    stream << "flw fa"<< context.opReg + 1 << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                    stream << "fmul.s fa"<< context.opReg << ",fa" << context.opReg + 1 << ",fa" << context.opReg  << std::endl;
                    stream << "fsw fa"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;

                }else if (context.Type(identifier_->GetStr()) == "double"){
                    stream << "fld fa"<< context.opReg + 1 << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                    stream << "fmul.d fa"<< context.opReg << ",fa" << context.opReg + 1 << ",fa" << context.opReg  << std::endl;
                    stream << "fsd fa"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;

                }else{

                    context.storeLoad = 0;
                    identifier_->EmitRISC(stream, context);
                }
            }
            context.opReg-=1;
        }else if(assignment_operator_ == "/="){
            context.storeLoad = 1;
            assignment_expression_->EmitRISC(stream, context);
            context.storeLoad = 0;
            if(identifier_->IsArray()){
                context.opReg++;
                context.storeLoad = 0;
                identifier_->EmitRISC(stream, context);
                context.opReg--;
            }else{

                if(context.Type(identifier_->GetStr()) == "int"){
                    stream << "lw a" << context.opReg + 1 << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                    stream << "div a" << context.opReg << ",a" << context.opReg + 1 << ",a" << context.opReg << std::endl;
                    stream << "sw a"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;

                }else if (context.Type(identifier_->GetStr()) == "float"){
                    stream << "flw fa"<< context.opReg + 1 << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                    stream << "fdiv.s fa"<< context.opReg << ",fa" << context.opReg + 1 << ",fa" << context.opReg  << std::endl;
                    stream << "fsw fa"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                }else if (context.Type(identifier_->GetStr()) == "double"){
                    stream << "fld fa"<< context.opReg + 1 << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                    stream << "fdiv.d fa"<< context.opReg << ",fa" << context.opReg + 1 << ",fa" << context.opReg  << std::endl;
                    stream << "fsd fa"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                }else{

                    context.storeLoad = 0;
                    identifier_->EmitRISC(stream, context);
                }
            }
            context.opReg-=1;
        }else if(assignment_operator_ == "%="){
            context.storeLoad = 1;
            assignment_expression_->EmitRISC(stream, context);
            context.storeLoad = 0;
            if(identifier_->IsArray()){
                context.opReg++;
                context.storeLoad = 0;
                identifier_->EmitRISC(stream, context);
                context.opReg--;
            }else{

                if(context.Type(identifier_->GetStr()) == "int"){
                    stream << "lw a" << context.opReg + 1 << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;
                    stream << "rem a" << context.opReg << ",a" << context.opReg + 1 << ",a" << context.opReg << std::endl;
                    stream << "sw a"<< context.opReg << ",-" << context.Offset(identifier_->GetStr()) << "(s0)" << std::endl;

                }else{

                    context.storeLoad = 0;
                    identifier_->EmitRISC(stream, context);
                }
            }
            context.opReg-=1;
        }
}

void AssignmentExpression::Print(std::ostream &stream) const
{
    stream << "AssignmentExpression: " << std::endl;
    identifier_->Print(stream);
    stream << " " << assignment_operator_ << " ";
    assignment_expression_->Print(stream);
    stream << ";" << std::endl;
}
