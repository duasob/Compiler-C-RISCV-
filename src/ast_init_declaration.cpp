#include "ast_init_declaration.hpp"

void InitDeclaration::EmitRISC(std::ostream &stream, Context &context) const
{


    //stream << "got " << context.Offset(declarator_->GetStr(), stream) << std::endl;
    //stream << "InitDeclaration: " << context.currentScope->name <<  std::endl;

    //stream << declarator_->IsPointer() << std::endl;
    if(context.currentScope->name == "root"){
        //global variable
        if(!declarator_->IsFunction()){
            GlobalDeclaration(stream, context);
        }

    }


    else if(context.Offset(declarator_->GetStr(), stream) == 0){
        if(!declarator_->IsFunction()){
            int size;
            std::string type = context.currentScope->variableTypeMap[declarator_->GetStr()];
            if(declarator_->IsArray()){
                size = context.calculateSize(type, true, declarator_->GetParamSize());
                context.currentScope->variableOffsetMap[declarator_->GetStr()] = context.calculateVarOffset(size, stream);
                context.currentScope->arrayTypeMap[declarator_->GetStr()] = "array";
                context.currentScope->arraySizeMap[declarator_->GetStr()] = declarator_->GetParamSize();
            }else {
                if (declarator_->IsPointer()){
                size = context.calculateSize(type, false, 0);
                context.currentScope->variableOffsetMap[declarator_->GetStr()] = context.calculateVarOffset(size, stream);
                context.currentScope->arrayTypeMap[declarator_->GetStr()] = "pointer";
                }else{
                    size = context.calculateSize(type, false, 0);
                    context.currentScope->variableOffsetMap[declarator_->GetStr()] = context.calculateVarOffset(size, stream);
                }

            }

        }

    }else{
        //if already declared
    }

    if (initializer_ != nullptr)
    {
        initializer_->EmitRISC(stream, context);
        if (declarator_->IsArray())
        {
            stream << "sw a" << context. opReg << ", -" << context.currentScope->variableOffsetMap[declarator_->GetStr()] << "(s0)" << std::endl;
        }if (declarator_->IsPointer()){
            stream << "sw a" << context. opReg << ", -" << context.currentScope->variableOffsetMap[declarator_->GetStr()] << "(s0)" << std::endl;
        }else
        {
            if(context.Type(declarator_->GetStr())=="int"){
                stream << "sw a" << context. opReg << ", -" << context.currentScope->variableOffsetMap[declarator_->GetStr()] << "(s0)" << std::endl;
            }else if (context.Type(declarator_->GetStr())=="float"){
                stream << "fsw fa" << context. opReg << ", -" << context.currentScope->variableOffsetMap[declarator_->GetStr()] << "(s0)" << std::endl;
            }else if (context.Type(declarator_->GetStr())=="double"){
                stream << "fsd fa" << context. opReg << ", -" << context.currentScope->variableOffsetMap[declarator_->GetStr()] << "(s0)" << std::endl;
            }
        }

    }
}

void InitDeclaration::Print(std::ostream &stream) const
{
    declarator_->Print(stream);
    if (initializer_ != nullptr)
    {
        stream << " = ";
        initializer_->Print(stream);
    }
    stream << ";" << std::endl;
}


void InitDeclaration::InitTypeMap(Context &context, std::string type) const{
    context.currentScope->variableTypeMap[declarator_->GetStr()] = type;
}



void InitDeclaration::GlobalDeclaration(std::ostream &stream, Context &context) const{
    int size;
    std::string type = context.currentScope->variableTypeMap[declarator_->GetStr()];
    stream << ".text" << std::endl;
    stream << ".globl    " << declarator_->GetStr() << std::endl;
    stream << ".bss" << std::endl;
    //stream << ".align   2" << std::endl;
    stream << ".type    " << declarator_->GetStr() << ", @object" << std::endl;

    if(declarator_->IsArray()){
        size = context.calculateSize(type, true, declarator_->GetParamSize());
    }else{
        size = context.calculateSize(type, false, 0);
    }
    stream << ".size    " << declarator_->GetStr() << ", " << size  << std::endl;
    stream << declarator_->GetStr() << ":" << std::endl;
    if (initializer_ == nullptr)
    {
        stream << ".zero    " << size << std::endl;
    }else{
        //improve this for arrays
        if(declarator_->IsArray()){
            stream << ".zero    " << size << std::endl;
        }else{
        stream << ".word    ";
        initializer_->Print(stream);
        stream << std::endl;
        }
    }
}
