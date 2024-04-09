#include "ast_type_specifier.hpp"

void TypeSpecifier::EmitRISC(std::ostream &stream, Context &context) const {
 //`            ;-.          ___,
 //             `.`\_...._/`.-"`
 //               \        /      ,
 //               /()   () \    .' `-._
 //              |)  .    ()\  /   _.'
 //              \  -'-     ,; '. <
 //               ;.__     ,;|   > /
 //              / ,    / ,  |.-'.-'
 //             (_/    (_/ ,;|.<`
 //               \    ,     ;-`
 //                >   \    /
 //               (_,-'`> .'
 //                     (_,'
}

void TypeSpecifier::Print(std::ostream &stream) const
{
    stream << type_;
}
