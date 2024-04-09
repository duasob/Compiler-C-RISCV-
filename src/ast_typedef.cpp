#include "ast_typedef.hpp"

void Typedef::EmitRISC(std::ostream &stream, Context &context) const {
    if (type_ == "typdef"){
        declaration_specifiers_->EmitRISC(stream, context);
    }else{
        
    }
}

void Typedef::Print(std::ostream &stream) const
{
    stream << type_;
}
