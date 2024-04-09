#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "ast_type_specifier.hpp"
#include "ast_identifier.hpp"
#include "ast_direct_declarator.hpp"
#include "ast_function_definition.hpp"

#include "ast_jump_statement.hpp"
#include "ast_node.hpp"

#include "ast_constant.hpp"
#include "ast_context.hpp"
#include "ast_expression.hpp"
#include "ast_expression_operations.hpp"
#include "ast_assignment_expression.hpp"

#include "ast_declaration.hpp"
#include "ast_compound_statement.hpp"
#include "ast_init_declaration.hpp"
#include "ast_init_declaration_list.hpp"
#include "ast_parameter_declaration.hpp"
#include "ast_control.hpp"
#include "ast_array.hpp"
#include "ast_pointer.hpp"
#include "ast_unary.hpp"
#include "ast_sizeof.hpp"
#include "ast_typedef.hpp"


extern Context context;
extern Node *ParseAST(std::string file_name);


#endif
