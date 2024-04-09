#include "ast_control.hpp"

void ControlIfElse::EmitRISC(std::ostream &stream, Context &context) const
{
    context.AddScopeTree("control");
    ifCondition_->EmitRISC(stream, context);
    stream << "beq a" << context.opReg << ", zero, .L" << context.labelCounter++ << std::endl;
    int ifLabel = context.labelCounter - 1;
    ifStatement_->EmitRISC(stream, context);
    int elseLabel;
    if(elseStatement_ != nullptr){
        stream << "j .L" << context.labelCounter++ << std::endl;
        elseLabel = context.labelCounter - 1;
    }
    stream << ".L" << ifLabel << ":" << std::endl;
    if(elseStatement_ != nullptr){
        elseStatement_->EmitRISC(stream, context);
        stream << ".L" << elseLabel << ":" << std::endl;
    }
    context.RemoveScopeTree();
}

void ControlIfElse::Print(std::ostream &stream) const
{
    stream << "if (" << std::endl;
    ifCondition_->Print(stream);
    stream << ") {";
    ifStatement_->Print(stream);
    stream << "}";
    if (elseStatement_ != nullptr)
    {
        stream << " else {";
        elseStatement_->Print(stream);
        stream << "}";
    }
}

void ControlWhile::EmitRISC(std::ostream &stream, Context &context) const
{
    context.AddScopeTree("control");
    int whileLabel1 = context.labelCounter;
    if(!isDoWhile_){
        stream << "j .L" << context.labelCounter << std::endl;
    }
    context.labelCounter++;
    int whileLabel2 = context.labelCounter;
    stream << ".L" << context.labelCounter++<< ":" << std::endl;
    whileStatement_->EmitRISC(stream, context);

    stream << ".L" << whileLabel1 << ":" << std::endl;
    whileCondition_->EmitRISC(stream, context);
    stream << "bne a" << context.opReg << ", zero, .L" << whileLabel2 << std::endl;
    context.RemoveScopeTree();
}

void ControlWhile::Print(std::ostream &stream) const
{
    stream << "while (" << std::endl;
    whileCondition_->Print(stream);
    stream << ") {";
    whileStatement_->Print(stream);
    stream << "}";
}

void ControlFor::EmitRISC(std::ostream &stream, Context &context) const
{
    context.AddScopeTree("control");
    forInit_->EmitRISC(stream, context);
    int forLabel1 = context.labelCounter;
    stream << "j .L" << context.labelCounter++ << std::endl;
    int forLabel2 = context.labelCounter;
    stream << ".L" << context.labelCounter++ << ":" << std::endl;
    forStatement_->EmitRISC(stream, context);
    forIncrement_->EmitRISC(stream, context);
    stream << ".L" << forLabel1 << ":" << std::endl;
    forCondition_->EmitRISC(stream, context);
    stream << "bne a" << context.opReg << ", zero, .L" << forLabel2 << std::endl;
    context.RemoveScopeTree();
}

void ControlFor::Print(std::ostream &stream) const
{
    stream << "for (" << std::endl;
    if(forInit_ != nullptr){
        forInit_->Print(stream);
    }

    stream << "; ";
    forCondition_->Print(stream);
    stream << "; ";
    forIncrement_->Print(stream);
    stream << ") {";
    forStatement_->Print(stream);
    stream << "}";
}

void ControlSwitch::EmitRISC(std::ostream &stream, Context &context) const
{
    context.AddScopeTree("control");
    context.caseState = 0;
    int labelStart = ++context.labelCounter;
    expression_->EmitRISC(stream, context);
    context.opReg++;
    statement_->EmitRISC(stream, context);

    if(context.caseDefault != 0){
        stream << "j .L" << context.caseDefault << std::endl;

    }else{
        stream << "j .L" << context.labelCounter << std::endl;
    }
    context.breakLabel = context.labelCounter;
    context.labelCounter = labelStart;
    context.caseState = 1;
    statement_->EmitRISC(stream, context);
    stream << ".L" << context.breakLabel << ":" << std::endl;
    context.caseDefault = 0;
    context.breakLabel = 0;
    context.RemoveScopeTree();

}

void ControlSwitch::Print(std::ostream &stream) const
{
    stream << "switch (" << std::endl;
    expression_->Print(stream);
    stream << ") {";
    statement_->Print(stream);
    stream << "}";
}

void ControlCase::EmitRISC(std::ostream &stream, Context &context) const
{
    //stream << context.opReg << std::endl;
    context.AddScopeTree("case");
    if(!context.caseState){
        if(expression_ != nullptr){
            expression_->EmitRISC(stream, context);
            stream << "beq a" << context.opReg -1 << ",a" << context.opReg  << " , .L" << context.labelCounter++ << std::endl;
            context.opReg -=2;
        }else{
            context.caseDefault = context.labelCounter++;
            context.opReg--;
        }
    }else{
        context.opReg -=1;
        stream << ".L" << context.labelCounter++ << ":" << std::endl;
        statement_->EmitRISC(stream, context);
    }
    context.RemoveScopeTree();
    context.opReg--;
}

void ControlCase::Print(std::ostream &stream) const
{
    stream << "case";
    if (expression_ != nullptr)
    {
        expression_->Print(stream);
    }
    else
    {
        stream << "default";
    }
    stream << ":";
    statement_->Print(stream);
}

void ControlBreak::EmitRISC(std::ostream &stream, Context &context) const
{

    if(context.caseState){
     stream << "j .L" << context.breakLabel << std::endl;
    }else{
        context.opReg --;
    }
}

void ControlBreak::Print(std::ostream &stream) const
{
    stream << "break;";
}
