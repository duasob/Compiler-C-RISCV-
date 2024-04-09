#ifndef AST_CONTEXT_HPP
#define AST_CONTEXT_HPP
#include <map>
#include <string>
#include <vector>
#include <iostream>
class Context
{

    public:
        //Reg Allocation
        int opRegBase = 0;                          //base registers, to return to after scope
        int opReg = 0;                              //current register
        int tReg = 0;                               //temporary register
        int sReg = 0;                               //save register

        //General
        int storeLoad = 0;                          //"bool" to determine store/load
        int labelCounter = 0;                       //label counter
        int labelTCounter = 0;                      //label counter for stack allocation "hack"

        // Switch
        int caseState = 0;
        int caseDefault = 0;
        int breakLabel = 0;

        //Stack Allocation
        int parameterStackSize = 0;
        int parameterStackPointer = 0;
        std::vector<int> stackSize = {0};
        std::vector<int> statementStackSize = {0};                    //statement stack size for each function
        std::vector<int> statementStackPointer = {0};                //statement number of allocated space.


        // Variable Information Maps
        std::string opType = "int";
        std::map<std::string, int> paramInitMap;
        std::map<std::string, int> floatConstMap;
        std::map<std::string, std::string> stringDeclareMap;
        std::vector<std::string> functionType;
        std::vector<std::map<std::string, std::string>> functionParameterMap;

        //Scope Information
        struct ScopeTree{
            ScopeTree* parent;
            std::map<std::string, std::string> variableTypeMap; //variable name to type
            std::map<std::string, int> variableOffsetMap; //variable name to offset
            std::map<std::string, std::string> arrayTypeMap; //array name to type
            std::map<std::string, int> arraySizeMap; //array name to size
            std::string name;

            ScopeTree(std::string n="not defined at Init") : parent(nullptr), variableTypeMap(std::map<std::string, std::string>()), variableOffsetMap(std::map<std::string, int>()), arrayTypeMap(std::map<std::string, std::string>()), name(n){};
        };

        ScopeTree* currentScope = new ScopeTree("root");
        std::vector<ScopeTree*> previousScope = {nullptr};

        //calculate the offset of a variable in the stack
        int Offset(std::string varName, std::ostream &stream = std::cout){
            ScopeTree* current = currentScope;
            while (current != nullptr){
                if (current->variableOffsetMap[varName] != 0 && (!current->variableOffsetMap.empty() || current->variableOffsetMap.find(varName) != current->variableOffsetMap.end())){
                    return current->variableOffsetMap[varName];
                }
                current = current->parent;
            }
            return 0;
        }

        //calculate the offset of a parameter in the stack
        int calculateParamOffset(std::string varName, std::ostream &stream = std::cout){
            std::string type = Type(varName, stream);
            if ((type == "int") | (type == "float")){
                this->parameterStackPointer += 4;
            }if (type == "double"){
                if (this->parameterStackPointer % 8 != 0){
                    this->parameterStackPointer += 4;
                }
                this->parameterStackPointer += 8;
            }
            if (this->parameterStackPointer > this->parameterStackSize){
                stream << "addi sp, sp, -" << this->parameterStackSize << std::endl;
                this->stackSize.back() += this->parameterStackSize;
                this->parameterStackSize *= 2;
            }
            return (16 + this->parameterStackPointer);
        }

        // calculate the size needed in the stack
        int calculateSize (std::string type, bool isArray, int arrSize){
            if(isArray){
                if (type == "int" || type == "float" || type == "char"){
                    return 4*arrSize;
                }else if (type == "double"){
                    return 8*arrSize;
                }
            }else{
                if (type == "int" || type == "float" || type == "char"){
                    return 4;
                }else if (type == "double"){
                    return 8;
                }
            }
            return 0;
        }

        //calculate variable offset in the stack
        int calculateVarOffset(int size, std::ostream &stream = std::cout){
           this->statementStackPointer.back() += size;
           int pointer = this->statementStackSize.back();
            if (this->statementStackPointer.back() > pointer){
                int offset = 16;
                while (this->statementStackPointer.back() > pointer){
                    if (pointer != 0){
                        offset = pointer*2;
                    }
                    pointer += offset;
                }

                stream << "beq t" << this->tReg << ", zero, .T" << this->labelTCounter << std::endl;
                stream << "addi sp, sp, -" << offset << std::endl;
                stream << "mv t"<< this->tReg << ", zero" << std::endl;
                stream << "li t"<< ++this->tReg << ", 1" << std::endl;
                stream << ".T" << this->labelTCounter++ << ":" << std::endl;

                this->stackSize.back() += offset;
                this->statementStackSize.back() += offset;
            }
            return (16 + this->parameterStackSize + this->statementStackPointer.back());
        }

        // return the type of a variable
        std::string Type(std::string varName, std ::ostream &stream = std::cout){
            ScopeTree* current = currentScope;
                while (current != nullptr){
                    if (current->variableTypeMap[varName] != "" && (!current->variableTypeMap.empty() || current->variableTypeMap.find(varName) != current->variableTypeMap.end())){
                        return current->variableTypeMap[varName];
                    }
                    current = current->parent;
                }
                return "not found";
        }

        //return the array type (pointer or array) of a variable
        std::string ArrayType(std::string varName, std ::ostream &stream = std::cout){
            ScopeTree* current = currentScope;
            while (current != nullptr){
                if (current->arrayTypeMap[varName] != "" && (!current->arrayTypeMap.empty() || current->arrayTypeMap.find(varName) != current->arrayTypeMap.end())){
                    return current->arrayTypeMap[varName];
                }
                current = current->parent;
            }
            stream << "not found" << std::endl;
            return "not found";
        }

        //return the size of an array
        int ArraySize(std::string varName, std ::ostream &stream = std::cout){
            ScopeTree* current = currentScope;
            while (current != nullptr){
                if (current->arraySizeMap[varName] != 0 && (!current->arraySizeMap.empty() || current->arraySizeMap.find(varName) != current->arraySizeMap.end())){
                    return current->arraySizeMap[varName];
                }
                current = current->parent;
            }
            return 0;
        }

        //enter a new scope
        void AddScopeTree(std::string name="not defined at AddScopeTree()", ScopeTree* tmpScope = nullptr, std::ostream &stream = std::cout){
            if (tmpScope == nullptr){
                tmpScope = currentScope;
            }
            opRegBase = opReg;
            previousScope.push_back(currentScope);
            currentScope = new ScopeTree(name);
            currentScope->parent = tmpScope;
        }

        // exit the current scope
        void RemoveScopeTree(){
            opReg = opRegBase;
            ScopeTree* tmpScope = currentScope;
            currentScope = previousScope.back();
            previousScope.pop_back();
            delete tmpScope;
        }

};

#endif
