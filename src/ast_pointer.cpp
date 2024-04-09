#include "ast_pointer.hpp"



void Pointer::EmitRISC(std::ostream &stream, Context &context) const
{
    if (context.currentScope->arrayTypeMap.empty() || context.currentScope->arrayTypeMap.find(identifier_) == context.currentScope->arrayTypeMap.end()) {
        context.currentScope->arrayTypeMap[identifier_] = "pointer";
    }else{
        // already declared
    }
    if (context.storeLoad){
        // normally handled as an identifier
    }else{
        // also handled by identifier
    }

}

void Pointer::Print(std::ostream &stream) const
{
    stream << "pointer: " << identifier_;
}



