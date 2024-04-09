#include "ast_constant.hpp"

void IntConstant::EmitRISC(std::ostream &stream, Context &context) const
{
    stream << "li a" << context.opReg << ", " << value_ << std::endl;
}

void IntConstant::Print(std::ostream &stream) const
{
    stream << value_;
}

union FloatToInt {
    float f;
    unsigned int i;
};

void FloatConstant::EmitRISC(std::ostream &stream, Context &context) const
{
    //this will need to be changed
    FloatToInt converter;
    converter.f = value_;
    context.floatConstMap[".LC0"] = converter.i;

    stream << "lui a" << context.opReg << ",%hi(.LC" << context.labelCounter << ")" << std::endl;
    stream << "flw fa" << context.opReg << ", %lo(.LC" << context.labelCounter << ")(a" << context.opReg << ")" << std::endl;
    context.labelCounter++;
}

void FloatConstant::Print(std::ostream &stream) const
{
    stream << value_;
}

void CharConstant::EmitRISC(std::ostream &stream, Context &context) const
{
    stream << "li a" << context.opReg << ", " << value_ << std::endl;
}

void CharConstant::Print(std::ostream &stream) const
{
    stream << value_;
}


void StringConstant::EmitRISC(std::ostream &stream, Context &context) const
{
    stream << "lui a" << context.opReg << ",%hi(.LC" << context.labelCounter << ")" << std::endl;
    stream << "addi a" << context.opReg << ", a" << context.opReg << ", %lo(.LC" << context.labelCounter << ")" << std::endl;
    context.stringDeclareMap[".LC"+std::to_string(context.labelCounter)] = value_;
    context.labelCounter++;

}

void StringConstant::Print(std::ostream &stream) const
{
    stream << value_;
}
