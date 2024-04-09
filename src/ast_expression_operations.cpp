#include "ast_expression_operations.hpp"

std::map<std::string, int> typeToShift = {  {"char", 0},
                                            {"int",2},
                                            {"float",2},
                                            {"double",3},
                                            };

void ExpressionAdd::EmitRISC(std::ostream &stream, Context &context) const
{
    context.opReg += 1;
    left_->EmitRISC(stream, context);
    if (right_->IsFunction()){
        stream << "mv s"<< ++context.sReg << ", a" << context.opReg  << std::endl;
        context.opReg += 1;
        right_->EmitRISC(stream, context);
        stream << "mv a" << context.opReg - 1 << ", s1" << std::endl;
    }else {
        context.opReg += 1;
        right_->EmitRISC(stream, context);
    }

    if(context.ArrayType(left_->GetStr()) == "pointer" ){
        stream << "slli" << " a" << context.opReg  << ", a" << context.opReg  << "," << typeToShift[context.Type(left_->GetStr())] << std::endl;
    }else if(context.ArrayType(right_->GetStr()) == "pointer"){
        stream << "slli" << " a" << context.opReg - 1 << ", a" << context.opReg - 1 << ", " << typeToShift[context.Type(right_->GetStr())]  << std::endl;
    }

    if(context.opType == "int"){
        stream << "add a" << context.opReg - 2 << ", a" << context.opReg - 1 <<", a" << context.opReg  << std::endl;
    }else if (context.opType == "float"){
        stream << "fadd.s fa" << context.opReg - 2 << ", fa" << context.opReg - 1 <<", fa" << context.opReg << std::endl;
    }else if (context.opType == "double"){
        stream << "fadd.d fa" << context.opReg - 2 << ", fa" << context.opReg - 1 <<", fa" << context.opReg << std::endl;
    }
    context.opReg -= 2;

}

void ExpressionAdd::Print(std::ostream &stream) const
{
    left_->Print(stream);
    stream << " + ";
    right_->Print(stream);
}

void ExpressionMul::EmitRISC(std::ostream &stream, Context &context) const
{
    context.opReg += 1;
    left_->EmitRISC(stream, context);


    if (right_->IsFunction()){
        stream << "mv s"<< ++context.sReg << ", a" << context.opReg  << std::endl;
        context.opReg += 1;
        right_->EmitRISC(stream, context);
        stream << "mv a" << context.opReg - 1 << ", s1" << std::endl;
    }else {
        context.opReg += 1;
        right_->EmitRISC(stream, context);
    }


    if(context.opType == "int"){
        stream << "mul a" << context.opReg -2 << ",a"<< context.opReg -1 << ", a" << context.opReg  << std::endl;
    }else if (context.opType == "float"){
        stream << "fmul.s fa" << context.opReg -2 << ", fa"<< context.opReg -1 << ", fa" << context.opReg << std::endl;
    }else if (context.opType == "double"){
        stream << "fmul.d fa" << context.opReg -2 << ", fa"<< context.opReg -1 << ", fa" << context.opReg << std::endl;
    }
    context.opReg -= 2;

}

void ExpressionMul::Print(std::ostream &stream) const
{
    left_->Print(stream);
    stream << " * ";
    right_->Print(stream);
}

void ExpressionBitOr::EmitRISC(std::ostream &stream, Context &context) const
{
    context.opReg += 1;
    left_->EmitRISC(stream, context);


    if (right_->IsFunction()){
        stream << "mv s"<< ++context.sReg << ", a" << context.opReg  << std::endl;
        context.opReg += 1;
        right_->EmitRISC(stream, context);
        stream << "mv a" << context.opReg - 1 << ", s1" << std::endl;
    }else {
        context.opReg += 1;
        right_->EmitRISC(stream, context);
    }
    stream << "or   a" << context.opReg -2 << ",a"<< context.opReg -1 << ",a" << context.opReg  << std::endl;

    context.opReg -= 2;

}

void ExpressionBitOr::Print(std::ostream &stream) const
{
    left_->Print(stream);
    stream << " | ";
    right_->Print(stream);
}

void ExpressionBitAnd::EmitRISC(std::ostream &stream, Context &context) const
{
    context.opReg += 1;
    left_->EmitRISC(stream, context);


    if (right_->IsFunction()){
        stream << "mv s"<< ++context.sReg << ", a" << context.opReg  << std::endl;
        context.opReg += 1;
        right_->EmitRISC(stream, context);
        stream << "mv a" << context.opReg - 1 << ", s1" << std::endl;
    }else {
        context.opReg += 1;
        right_->EmitRISC(stream, context);
    }
    stream << "and   a" << context.opReg -2 << ",a"<< context.opReg -1 << ",a" << context.opReg  << std::endl;

    context.opReg -= 2;
}

void ExpressionBitAnd::Print(std::ostream &stream) const
{

    left_->Print(stream);
    stream << " & ";
    right_->Print(stream);
}

void ExpressionBitXor::EmitRISC(std::ostream &stream, Context &context) const
{
    context.opReg += 1;
    left_->EmitRISC(stream, context);


    if (right_->IsFunction()){
        stream << "mv s"<< ++context.sReg << ", a" << context.opReg  << std::endl;
        context.opReg += 1;
        right_->EmitRISC(stream, context);
        stream << "mv a" << context.opReg - 1 << ", s1" << std::endl;
    }else {
        context.opReg += 1;
        right_->EmitRISC(stream, context);
    }
    stream << "xor   a" << context.opReg -2 << ",a"<< context.opReg -1 << ",a" << context.opReg  << std::endl;

    context.opReg -= 2;
}

void ExpressionBitXor::Print(std::ostream &stream) const
{

    left_->Print(stream);
    stream << " ^ ";
    right_->Print(stream);

}

void ExpressionLessThan::EmitRISC(std::ostream &stream, Context &context) const
{
    context.opReg += 1;
    left_->EmitRISC(stream, context);


    if (right_->IsFunction()){
        stream << "mv s"<< ++context.sReg << ", a" << context.opReg  << std::endl;
        context.opReg += 1;
        right_->EmitRISC(stream, context);
        stream << "mv a" << context.opReg - 1 << ", s1" << std::endl;
    }else {
        context.opReg += 1;
        right_->EmitRISC(stream, context);
    }

    if(context.opType == "int"){
    stream << "slt   a" << context.opReg -2 << ",a"<< context.opReg -1 << ",a" << context.opReg  << std::endl;
    stream << "andi  a" << context.opReg -2 << ",a"<< context.opReg -2 << ",0xff" << std::endl;
    }else if (context.opType == "float"){
        stream << "flt.s  a" << context.opReg -2 << ",fa"<< context.opReg -1 << ",fa" << context.opReg  << std::endl;
        stream << "andi  a" << context.opReg -2 << ",a"<< context.opReg -2 << ",0xff" << std::endl;
    }else if (context.opType == "double"){
        stream << "flt.d  a" << context.opReg -2 << ",fa"<< context.opReg -1 << ",fa" << context.opReg  << std::endl;
        stream << "andi  a" << context.opReg -2 << ",a"<< context.opReg -2 << ",0xff" << std::endl;
    }
    context.opReg -= 2;
}

void ExpressionLessThan::Print(std::ostream &stream) const
{

    left_->Print(stream);
    stream << " < ";
    right_->Print(stream);
}

void ExpressionGreaterThan::EmitRISC(std::ostream &stream, Context &context) const
{
    context.opReg += 1;
    left_->EmitRISC(stream, context);
    if (right_->IsFunction()){
        stream << "mv s"<< ++context.sReg << ", a" << context.opReg  << std::endl;
        context.opReg += 1;
        right_->EmitRISC(stream, context);
        stream << "mv a" << context.opReg - 1 << ", s1" << std::endl;
    }else {
        context.opReg += 1;
        right_->EmitRISC(stream, context);
    }
    if(context.opType == "int"){
    stream << "sgt   a" << context.opReg -2 << ",a"<< context.opReg -1 << ",a" << context.opReg  << std::endl;
    stream << "andi   a" << context.opReg -2 << ",a"<< context.opReg -2 << ",0xff" << std::endl;
    context.opReg -= 2;
    } else if (context.opType == "float"){
        stream << "fgt.s  a" << context.opReg -2 << ",fa"<< context.opReg -1 << ",fa" << context.opReg  << std::endl;
        stream << "andi   a" << context.opReg -2 << ",a"<< context.opReg -2 << ",0xff" << std::endl;
        context.opReg -= 2;
    }else if (context.opType == "double"){
        stream << "fgt.d  a" << context.opReg -2 << ",fa"<< context.opReg -1 << ",fa" << context.opReg  << std::endl;
        stream << "andi   a" << context.opReg -2 << ",a"<< context.opReg -2 << ",0xff" << std::endl;
        context.opReg -= 2;
    }

}

void ExpressionGreaterThan::Print(std::ostream &stream) const
{

    left_->Print(stream);
    stream << " > ";
    right_->Print(stream);
}

void ExpressionLessEqual ::EmitRISC(std::ostream &stream, Context &context) const
{
    context.opReg += 1;
    left_->EmitRISC(stream, context);
    if (right_->IsFunction()){
        stream << "mv s"<< ++context.sReg << ", a" << context.opReg  << std::endl;
        context.opReg += 1;
        right_->EmitRISC(stream, context);
        stream << "mv a" << context.opReg - 1 << ", s1" << std::endl;
    }else {
        context.opReg += 1;
        right_->EmitRISC(stream, context);
    }
    if(context.opType == "int"){
    stream << "sgt   a" << context.opReg -2 << ",a"<< context.opReg -1 << ",a" << context.opReg  << std::endl;
    stream << "xori   a" << context.opReg -2 << ",a"<< context.opReg -2 << ",1" << std::endl;
    stream << "andi   a" << context.opReg -2 << ",a"<< context.opReg -2 << ",0xff" << std::endl;
    context.opReg -= 2;
    } else if (context.opType == "float"){
        stream << "fgt.s  a" << context.opReg -2 << ",fa"<< context.opReg -1 << ",fa" << context.opReg  << std::endl;
        stream << "xori   a" << context.opReg -2 << ",a"<< context.opReg -2 << ",1" << std::endl;
        stream << "andi   a" << context.opReg -2 << ",a"<< context.opReg -2 << ",0xff" << std::endl;
        context.opReg -= 2;
    }else if (context.opType == "double"){
        stream << "fgt.d  a" << context.opReg -2 << ",fa"<< context.opReg -1 << ",fa" << context.opReg  << std::endl;
        stream << "xori   a" << context.opReg -2 << ",a"<< context.opReg -2 << ",1" << std::endl;
        stream << "andi   a" << context.opReg -2 << ",a"<< context.opReg -2 << ",0xff" << std::endl;
        context.opReg -= 2;
    }
    
}

void ExpressionLessEqual::Print(std::ostream &stream) const
{

    left_->Print(stream);
    stream << " <= ";
    right_->Print(stream);
}

void ExpressionGreaterEqual::EmitRISC(std::ostream &stream, Context &context) const
{
    context.opReg += 1;
    left_->EmitRISC(stream, context);
    if (right_->IsFunction()){
        stream << "mv s"<< ++context.sReg << ", a" << context.opReg  << std::endl;
        context.opReg += 1;
        right_->EmitRISC(stream, context);
        stream << "mv a" << context.opReg - 1 << ", s1" << std::endl;
    }else {
        context.opReg += 1;
        right_->EmitRISC(stream, context);
    }
    if(context.opType == "int"){
    stream << "slt   a" << context.opReg -2 << ",a"<< context.opReg -1 << ",a" << context.opReg  << std::endl;
    stream << "xori   a" << context.opReg -2 << ",a"<< context.opReg -2 << ",1" << std::endl;
    stream << "andi   a" << context.opReg -2 << ",a"<< context.opReg -2 << ",0xff" << std::endl;
    context.opReg -= 2;
    }else if (context.opType == "float"){
        stream << "flt.s  a" << context.opReg -2 << ",fa"<< context.opReg -1 << ",fa" << context.opReg  << std::endl;
        stream << "xori   a" << context.opReg -2 << ",a"<< context.opReg -2 << ",1" << std::endl;
        stream << "andi   a" << context.opReg -2 << ",a"<< context.opReg -2 << ",0xff" << std::endl;
        context.opReg -= 2;
    }else if (context.opType == "double"){
        stream << "flt.d  a" << context.opReg -2 << ",fa"<< context.opReg -1 << ",fa" << context.opReg  << std::endl;
        stream << "xori   a" << context.opReg -2 << ",a"<< context.opReg -2 << ",1" << std::endl;
        stream << "andi   a" << context.opReg -2 << ",a"<< context.opReg -2 << ",0xff" << std::endl;
        context.opReg -= 2;
    }
}

void ExpressionGreaterEqual::Print(std::ostream &stream) const
{

    left_->Print(stream);
    stream << " >= ";
    right_->Print(stream);
}

void ExpressionDiv::EmitRISC(std::ostream &stream, Context &context) const
{
    context.opReg += 1;
    left_->EmitRISC(stream, context);
    if (right_->IsFunction()){
        stream << "mv s"<< ++context.sReg << ", a" << context.opReg  << std::endl;
        context.opReg += 1;
        right_->EmitRISC(stream, context);
        stream << "mv a" << context.opReg - 1 << ", s1" << std::endl;
    }else {
        context.opReg += 1;
        right_->EmitRISC(stream, context);
    }
    if(context.opType == "int"){
        stream << "div a" << context.opReg -2 << ",a"<< context.opReg -1 << ", a" << context.opReg  << std::endl;
    }else if (context.opType == "float"){
        stream << "fdiv.s fa" << context.opReg -2 << ", fa"<< context.opReg -1 << ", fa" << context.opReg << std::endl;
    }else if (context.opType == "double"){
        stream << "fdiv.d fa" << context.opReg -2 << ", fa"<< context.opReg -1 << ", fa" << context.opReg << std::endl;
    }
    context.opReg -= 2;
}

void ExpressionDiv::Print(std::ostream &stream) const
{

    left_->Print(stream);
    stream << " / ";
    right_->Print(stream);
}

void ExpressionSub::EmitRISC(std::ostream &stream, Context &context) const
{
    //stream << "Sub" << std::endl;
    context.opReg += 1;
    left_->EmitRISC(stream, context);
    if (right_->IsFunction()){
        stream << "mv s"<< ++context.sReg << ", a" << context.opReg  << std::endl;
        context.opReg += 1;
        right_->EmitRISC(stream, context);
        stream << "mv a" << context.opReg - 1 << ", s1" << std::endl;
    }else {
        context.opReg += 1;
        right_->EmitRISC(stream, context);
    }

    if(context.ArrayType(left_->GetStr()) == "pointer" ){
        stream << "slli" << " a" << context.opReg  << ", a" << context.opReg  << ", " << typeToShift[context.Type(left_->GetStr())]  << std::endl;
    }else if(context.ArrayType(right_->GetStr()) == "pointer"){
        stream << "slli" << " a" << context.opReg - 1 << ", a" << context.opReg - 1 << ", " << typeToShift[context.Type(left_->GetStr())]  << std::endl;
    }

    if(context.opType == "int"){
        stream << "sub a" << context.opReg -2 << ",a"<< context.opReg -1 << ", a" << context.opReg  << std::endl;
    }else if (context.opType == "float"){
        stream << "fsub.s fa" << context.opReg -2 << ", fa"<< context.opReg -1 << ", fa" << context.opReg << std::endl;
    }else if (context.opType == "double"){
        stream << "fsub.d fa" << context.opReg -2 << ", fa"<< context.opReg -1 << ", fa" << context.opReg << std::endl;
    }
    context.opReg -= 2;
}

void ExpressionSub::Print(std::ostream &stream) const
{

    left_->Print(stream);
    stream << " - ";
    right_->Print(stream);
}

void ExpressionEqual::EmitRISC(std::ostream &stream, Context &context) const
{
    context.opReg += 1;
    left_->EmitRISC(stream, context);
    if (right_->IsFunction()){
        stream << "mv s"<< ++context.sReg << ", a" << context.opReg  << std::endl;
        context.opReg += 1;
        right_->EmitRISC(stream, context);
        stream << "mv a" << context.opReg - 1 << ", s1" << std::endl;
    }else {
        context.opReg += 1;
        right_->EmitRISC(stream, context);
    }
    if(context.opType == "int"){
    stream << "sub a" << context.opReg -2 << ",a"<< context.opReg -1 << ", a" << context.opReg  << std::endl;
    stream << "seqz   a" << context.opReg -2 << ",a"<< context.opReg -2 << std::endl;
    stream << "andi   a" << context.opReg -2 << ",a"<< context.opReg -2 << ",0xff" << std::endl;
    context.opReg -= 2;
    }else if (context.opType == "float"){
        stream << "feq.s  a" << context.opReg -2 << ",fa"<< context.opReg -1 << ",fa" << context.opReg  << std::endl;
        stream << "andi   a" << context.opReg -2 << ",a"<< context.opReg -2 << ",0xff" << std::endl;
        context.opReg -= 2;
    }else if (context.opType == "double"){
        stream << "feq.d  a" << context.opReg -2 << ",fa"<< context.opReg -1 << ",fa" << context.opReg  << std::endl;
        stream << "andi   a" << context.opReg -2 << ",a"<< context.opReg -2 << ",0xff" << std::endl;
        context.opReg -= 2;
    }
}

void ExpressionEqual::Print(std::ostream &stream) const
{

    left_->Print(stream);
    stream << " == ";
    right_->Print(stream);
}


void ExpressionLogicalAnd::EmitRISC(std::ostream &stream, Context &context) const
{
    context.opReg += 1;
    left_->EmitRISC(stream, context);
    stream << "beq a" << context.opReg << ",zero, .L" << context.labelCounter << std::endl;

    if (right_->IsFunction()){
        stream << "mv s"<< ++context.sReg << ", a" << context.opReg  << std::endl;
        context.opReg += 1;
        right_->EmitRISC(stream, context);
        stream << "mv a" << context.opReg - 1 << ", s1" << std::endl;
    }else {
        context.opReg += 1;
        right_->EmitRISC(stream, context);
    }
    stream << "beq a" << context.opReg << ",zero, .L" << context.labelCounter << std::endl;
    stream << "li a" << context.opReg << ", 1" << std::endl;
    stream << "j .L" << context.labelCounter + 1 << std::endl;
    stream << ".L" << context.labelCounter << ":" << std::endl;
    stream << "li a" << context.opReg << ", 0" << std::endl;
    stream << ".L" << context.labelCounter + 1 << ":" << std::endl;
    context.labelCounter += 2;

}

void ExpressionLogicalAnd::Print(std::ostream &stream) const
{

    left_->Print(stream);
    stream << " && ";
    right_->Print(stream);
}

void ExpressionLogicalOr::EmitRISC(std::ostream &stream, Context &context) const
{
    context.opReg += 1;
    left_->EmitRISC(stream, context);
    stream << "bne a" << context.opReg << ",zero, .L" << context.labelCounter << std::endl;

    if (right_->IsFunction()){
        stream << "mv s"<< ++context.sReg << ", a" << context.opReg  << std::endl;
        context.opReg += 1;
        right_->EmitRISC(stream, context);
        stream << "mv a" << context.opReg - 1 << ", s1" << std::endl;
    }else {
        context.opReg += 1;
        right_->EmitRISC(stream, context);
    }
    stream << "bne a" << context.opReg << ",zero, .L" << context.labelCounter << std::endl;
    stream << "li a" << context.opReg << ", 0" << std::endl;
    stream << "j .L" << context.labelCounter + 1 << std::endl;
    stream << ".L" << context.labelCounter << ":" << std::endl;
    stream << "li a" << context.opReg << ", 1" << std::endl;
    stream << ".L" << context.labelCounter + 1 << ":" << std::endl;
    context.labelCounter += 2;
}

void ExpressionLogicalOr::Print(std::ostream &stream) const
{

    left_->Print(stream);
    stream << " || ";
    right_->Print(stream);
}

void ExpressionMod::EmitRISC(std::ostream &stream, Context &context) const
{
    context.opReg += 1;
    left_->EmitRISC(stream, context);
    if (right_->IsFunction()){
        stream << "mv s"<< ++context.sReg << ", a" << context.opReg  << std::endl;
        context.opReg += 1;
        right_->EmitRISC(stream, context);
        stream << "mv a" << context.opReg - 1 << ", s1" << std::endl;
    }else {
        context.opReg += 1;
        right_->EmitRISC(stream, context);
    }
    stream << "rem a" << context.opReg -2 << ",a"<< context.opReg -1 << ", a" << context.opReg  << std::endl;
    context.opReg -= 2;
}

void ExpressionMod::Print(std::ostream &stream) const
{

    left_->Print(stream);
    stream << " % ";
    right_->Print(stream);
}

void ExpressionLeftShift::EmitRISC(std::ostream &stream, Context &context) const
{
    context.opReg += 1;
    left_->EmitRISC(stream, context);
    if (right_->IsFunction()){
        stream << "mv s"<< ++context.sReg << ", a" << context.opReg  << std::endl;
        context.opReg += 1;
        right_->EmitRISC(stream, context);
        stream << "mv a" << context.opReg - 1 << ", s1" << std::endl;
    }else {
        context.opReg += 1;
        right_->EmitRISC(stream, context);
    }

    stream << "sll a" << context.opReg -2 << ",a"<< context.opReg -1 << ", a" << context.opReg  << std::endl;
    context.opReg -= 2;
}

void ExpressionLeftShift::Print(std::ostream &stream) const
{

    left_->Print(stream);
    stream << " << ";
    right_->Print(stream);
}

void ExpressionRightShift::EmitRISC(std::ostream &stream, Context &context) const
{
    //stream << "sra" << std::endl;
    context.opReg += 1;
    left_->EmitRISC(stream, context);
    if (right_->IsFunction()){
        stream << "mv s"<< ++context.sReg << ", a" << context.opReg  << std::endl;
        context.opReg += 1;
        right_->EmitRISC(stream, context);
        stream << "mv a" << context.opReg - 1 << ", s1" << std::endl;
    }else {
        context.opReg += 1;
        right_->EmitRISC(stream, context);
    }
    stream << "sra a" << context.opReg -2 << ",a"<< context.opReg -1 << ", a" << context.opReg  << std::endl;
    context.opReg -= 2;
}

void ExpressionRightShift::Print(std::ostream &stream) const
{

    left_->Print(stream);
    stream << " >> " ;
    right_->Print(stream);
}

void ExpressionNotEqual::EmitRISC(std::ostream &stream, Context &context) const
{
    context.opReg += 1;
    left_->EmitRISC(stream, context);
    if (right_->IsFunction()){
        stream << "mv s"<< ++context.sReg << ", a" << context.opReg  << std::endl;
        context.opReg += 1;
        right_->EmitRISC(stream, context);
        stream << "mv a" << context.opReg - 1 << ", s1" << std::endl;
    }else {
        context.opReg += 1;
        right_->EmitRISC(stream, context);
    }
    if(context.opType == "int"){
        stream << "sub a" << context.opReg -2 << ",a"<< context.opReg -1 << ", a" << context.opReg  << std::endl;
        stream << "snez   a" << context.opReg -2 << ",a"<< context.opReg -2 << std::endl;
        stream << "andi   a" << context.opReg -2 << ",a"<< context.opReg -2 << ",0xff" << std::endl;
    context.opReg -= 2;
    }else if (context.opType == "float"){
        stream << "feq.s  a" << context.opReg -2 << ",fa"<< context.opReg -1 << ",fa" << context.opReg  << std::endl;
        stream << "seqz  a" << context.opReg -2 << ",a"<< context.opReg -2 << std::endl;
        stream << "andi   a" << context.opReg -2 << ",a"<< context.opReg -2 << ",0xff" << std::endl;
        context.opReg -= 2;
    }else if (context.opType == "double"){
        stream << "feq.d  a" << context.opReg -2 << ",fa"<< context.opReg -1 << ",fa" << context.opReg  << std::endl;
        stream << "seqz  a" << context.opReg -2 << ",a"<< context.opReg -2 << std::endl;
        stream << "andi   a" << context.opReg -2 << ",a"<< context.opReg -2 << ",0xff" << std::endl;
        context.opReg -= 2;
    }
}

void ExpressionNotEqual::Print(std::ostream &stream) const
{

    left_->Print(stream);
    stream << " != ";
    right_->Print(stream);
}


void ExpressionConditional::EmitRISC(std::ostream &stream, Context &context) const
{
    context.opReg += 1;
    condition_->EmitRISC(stream, context);
    stream << "beq a" << context.opReg << ",zero, .L" << context.labelCounter << std::endl;
    trueExpression_->EmitRISC(stream, context);
    stream << "j .L" << context.labelCounter + 1 << std::endl;
    stream << ".L" << context.labelCounter << ":" << std::endl;
    falseExpression_->EmitRISC(stream, context);
    stream << ".L" << context.labelCounter + 1 << ":" << std::endl;

    context.labelCounter += 2;
}

void ExpressionConditional::Print(std::ostream &stream) const
{

    condition_->Print(stream);
    stream << " ? ";
    trueExpression_->Print(stream);
    stream << " : ";
    falseExpression_->Print(stream);
}

void ExpressionPostInc::EmitRISC(std::ostream &stream, Context &context) const
{
    context.opReg += 1;
    expression_->EmitRISC(stream, context);
    if(context.ArrayType(expression_->GetStr()) == "pointer" ){
        stream << "addi a" << context.opReg << ", a" << context.opReg << ", " << context.calculateSize(context.Type(expression_->GetStr()), false, 0) << std::endl;
    }else{
        stream << "addi a" << context.opReg << ", a" << context.opReg << ", 1" << std::endl;
    }
    stream << "sw a" << context.opReg << ", " << -(context.Offset(expression_->GetStr()))<< "(s0)" << std::endl;

}

void ExpressionPostInc::Print(std::ostream &stream) const
{

    expression_->Print(stream);
    stream << "++";
}

void ExpressionPostDec::EmitRISC(std::ostream &stream, Context &context) const
{
    context.opReg += 2;
    expression_->EmitRISC(stream, context);
    if(context.ArrayType(expression_->GetStr()) == "pointer" ){
        stream << "addi a" << context.opReg-1 << ", a" << context.opReg << ", -"<< context.calculateSize(context.Type(expression_->GetStr()), false, 0) << std::endl;
    }else{
        stream << "addi a" << context.opReg - 1 << ", a" << context.opReg << ", -1" << std::endl;
    }

    stream << "sw a" << context.opReg - 1 << ", " << -(context.Offset(expression_->GetStr()))<< "(s0)" << std::endl;

}

void ExpressionPostDec::Print(std::ostream &stream) const
{

    expression_->Print(stream);
    stream << "--";
}

void ExpressionPreInc::EmitRISC(std::ostream &stream, Context &context) const
{
    context.opReg += 1;
    expression_->EmitRISC(stream, context);
    if(context.ArrayType(expression_->GetStr()) == "pointer" ){
        stream << "addi a" << context.opReg << ", a" << context.opReg << "," << context.calculateSize(context.Type(expression_->GetStr()), false, 0) << std::endl;
    }else{
        stream << "addi a" << context.opReg << ", a" << context.opReg << ", 1" << std::endl;
    }
    stream << "addi a" << context.opReg << ", a" << context.opReg << ", 1" << std::endl;
    stream << "sw a" << context.opReg << ", " << -(context.Offset(expression_->GetStr()))<< "(s0)" << std::endl;

}

void ExpressionPreInc::Print(std::ostream &stream) const
{

    stream << "++";
    expression_->Print(stream);
}

void ExpressionPreDec::EmitRISC(std::ostream &stream, Context &context) const
{
    context.opReg += 1;
    expression_->EmitRISC(stream, context);
    if(context.ArrayType(expression_->GetStr()) == "pointer" ){
        stream << "addi a" << context.opReg << ", a" << context.opReg << ",-" << context.calculateSize(context.Type(expression_->GetStr()), false, 0) << std::endl;
    }else{
        stream << "addi a" << context.opReg << ", a" << context.opReg << ",-1" << std::endl;
    }
    stream << "sw a" << context.opReg << ", " << -(context.Offset(expression_->GetStr()))<< "(s0)" << std::endl;

}

void ExpressionPreDec::Print(std::ostream &stream) const
{

    stream << "--";
    expression_->Print(stream);
}
