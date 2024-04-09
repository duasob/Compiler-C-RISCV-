// Adapted from: https://www.lysator.liu.se/c/ANSI-C-grammar-y.html

%code requires{
    #include "ast.hpp"
	#include <string.h>

    extern Node *g_root;
    extern FILE *yyin;
    int yylex(void);
    void yyerror(const char *);
}

// Represents the value associated with any kind of AST node.
%union{
  Node*										node;
  NodeList*									nodes;
  Identifier*								identifier;
  DirectDeclarator*							direct_declarator;
  TypeSpecifier*							type_specifier;
  Expression *								expression;
  InitDeclaration*							init_declaration;
  InitDeclarationList* 						init_declaration_list;
  int 										number_int;
  double       								number_float;
  std::string*								string;
  yytokentype  								token;
}

%token IDENTIFIER INT_CONSTANT FLOAT_CONSTANT STRING_LITERAL CHAR_LITERAL
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP
%token MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
%token TYPE_NAME TYPEDEF EXTERN STATIC AUTO REGISTER SIZEOF
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS
%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%type <node>  external_declaration function_definition declaration
%type <node>  struct_specifier struct_declaration_list struct_declaration specifier_qualifier_list struct_declarator_list
%type <node>  type_name abstract_declarator direct_abstract_declarator initializer  statement labeled_statement
%type <node> struct_declarator enum_specifier enumerator_list enumerator   parameter_declaration
%type <node> compound_statement jump_statement

%type <nodes> translation_unit argument_expression_list parameter_list
%type <nodes> initializer_list identifier_list declaration_list statement_list

%type <expression> postfix_expression primary_expression
%type <expression> unary_expression cast_expression multiplicative_expression additive_expression shift_expression relational_expression
%type <expression> equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression
%type <expression> conditional_expression assignment_expression expression constant_expression
%type <expression> expression_statement iteration_statement selection_statement

%type <init_declaration> init_declarator
%type <init_declaration_list> init_declarator_list
%type <type_specifier> declaration_specifiers
%type <type_specifier> type_specifier

%type <identifier> direct_declarator declarator



%type <string> unary_operator  storage_class_specifier assignment_operator pointer
%type <string> IDENTIFIER CHAR_LITERAL STRING_LITERAL TYPE_NAME

%type <number_int> INT_CONSTANT
%type <number_float> FLOAT_CONSTANT


%start ROOT
%%

ROOT
  : translation_unit { g_root = $1; }

translation_unit
	: external_declaration { $$ = new NodeList($1); }
	| translation_unit external_declaration { $1->PushBack($2); $$=$1; }
	;

external_declaration
	: function_definition { $$ = $1; }
	| declaration { $$ = $1; }
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement
	| declaration_specifiers declarator compound_statement { $$ = new FunctionDefinition($1, $2, $3); }
	| declarator declaration_list compound_statement
	| declarator compound_statement
	;


primary_expression
	: IDENTIFIER { $$ = new Identifier(*$1, false, nullptr); delete $1; }
	| INT_CONSTANT { $$ = new IntConstant(int($1)); }
    | FLOAT_CONSTANT { $$ = new FloatConstant($1); }
	| STRING_LITERAL { $$ = new StringConstant(*$1); delete $1; }
	| CHAR_LITERAL { $$ = new CharConstant(*$1); delete $1; }
	| '(' expression ')' { $$ = $2; }
	;

postfix_expression
	: primary_expression { $$ = $1;}
	| postfix_expression '[' expression ']' { $$ = new Array($1->GetStr(), 0, $3); }
	| postfix_expression '(' ')' { $$ = $1->ChangeIsFunction(true); }
	| postfix_expression '(' argument_expression_list ')' { $$ = $1->ChangeIsFunction(true, $3); }
	| postfix_expression '.' IDENTIFIER
	| postfix_expression PTR_OP IDENTIFIER
	| postfix_expression INC_OP { $$ = new ExpressionPostInc($1); }
	| postfix_expression DEC_OP { $$ = new ExpressionPostDec($1); }
	;

argument_expression_list
	: assignment_expression { $$ = new NodeList($1); }
	| argument_expression_list ',' assignment_expression { $1->PushBack($3); $$=$1; }
	;

unary_expression
	: postfix_expression { $$ = $1; }
	| INC_OP unary_expression { $$ = new ExpressionPreInc($2); }
	| DEC_OP unary_expression { $$ = new ExpressionPreDec($2); }
	| unary_operator cast_expression { $$ = new Unary(*$1, $2); delete $1; }
	| SIZEOF unary_expression { $$ = new SizeOf("",$2); }
	| SIZEOF '(' type_name ')'
	| SIZEOF '(' type_specifier ')'{$$ = new SizeOf($3->GetStr(), nullptr); delete $3;}
	;

unary_operator
	: '&' { $$ = new std::string("&"); }
	| '*' { $$ = new std::string("*"); }
	| '+' { $$ = new std::string("+"); }
	| '-' { $$ = new std::string("-"); }
	| '~' { $$ = new std::string("~"); }
	| '!' { $$ = new std::string("!"); }
	;

cast_expression
	: unary_expression { $$ = $1; }
	| '(' type_name ')' cast_expression
	;

multiplicative_expression
	: cast_expression { $$ = $1; }
	| multiplicative_expression '*' cast_expression { $$ = new ExpressionMul($1, $3); }
	| multiplicative_expression '/' cast_expression { $$ = new ExpressionDiv($1, $3); }
	| multiplicative_expression '%' cast_expression { $$ = new ExpressionMod($1, $3); }
	;

additive_expression
	: multiplicative_expression { $$ = $1; }
	| additive_expression '+' multiplicative_expression { $$ = new ExpressionAdd($1, $3);}
	| additive_expression '-' multiplicative_expression { $$ = new ExpressionSub($1, $3); }
	;

shift_expression
	: additive_expression { $$ = $1; }
	| shift_expression LEFT_OP additive_expression { $$ = new ExpressionLeftShift($1, $3); }
	| shift_expression RIGHT_OP additive_expression { $$ = new ExpressionRightShift($1, $3); }
	;

relational_expression
	: shift_expression { $$ = $1; }
	| relational_expression '<' shift_expression { $$ = new ExpressionLessThan($1, $3); }
	| relational_expression '>' shift_expression { $$ = new ExpressionGreaterThan($1, $3); }
	| relational_expression LE_OP shift_expression { $$ = new ExpressionLessEqual($1, $3); }
	| relational_expression GE_OP shift_expression { $$ = new ExpressionGreaterEqual($1, $3); }
	;

equality_expression
	: relational_expression { $$ = $1; }
	| equality_expression EQ_OP relational_expression { $$ = new ExpressionEqual($1, $3);}
	| equality_expression NE_OP relational_expression { $$ = new ExpressionNotEqual($1, $3); }
	;

and_expression
	: equality_expression { $$ = $1; }
	| and_expression '&' equality_expression { $$ = new ExpressionBitAnd($1, $3); }
	;

exclusive_or_expression
	: and_expression { $$ = $1; }
	| exclusive_or_expression '^' and_expression { $$ = new ExpressionBitXor($1, $3); }
	;

inclusive_or_expression
	: exclusive_or_expression { $$ = $1; }
	| inclusive_or_expression '|' exclusive_or_expression { $$ = new ExpressionBitOr($1, $3); }
	;

logical_and_expression
	: inclusive_or_expression  { $$ = $1; }
	| logical_and_expression AND_OP inclusive_or_expression { $$ = new ExpressionLogicalAnd($1, $3); }
	;

logical_or_expression
	: logical_and_expression { $$ = $1; }
	| logical_or_expression OR_OP logical_and_expression { $$ = new ExpressionLogicalOr($1, $3); }
	;

conditional_expression
	: logical_or_expression { $$ = $1; }
	| logical_or_expression '?' expression ':' conditional_expression { $$ = new ExpressionConditional($1, $3, $5); }
	;

assignment_expression
	: conditional_expression { $$ = $1; }
	| unary_expression assignment_operator assignment_expression {
		$$ = new AssignmentExpression($1, *$2, $3);
		delete $2;
		}
	;

assignment_operator
	: '=' { $$ = new std::string("=");}
	| MUL_ASSIGN { $$ = new std::string("*="); }
	| DIV_ASSIGN { $$ = new std::string("/="); }
	| MOD_ASSIGN { $$ = new std::string("%="); }
	| ADD_ASSIGN { $$ = new std::string("+="); }
	| SUB_ASSIGN { $$ = new std::string("-="); }
	| LEFT_ASSIGN { $$ = new std::string("<<="); }
	| RIGHT_ASSIGN { $$ = new std::string(">>="); }
	| AND_ASSIGN { $$ = new std::string("&="); }
	| XOR_ASSIGN { $$ = new std::string("^="); }
	| OR_ASSIGN { $$ = new std::string("|="); }
	;

expression
	: assignment_expression { $$ = $1; }
	| expression ',' assignment_expression
	;

constant_expression
	: conditional_expression
	;

declaration
	: declaration_specifiers ';'
	| declaration_specifiers init_declarator_list ';' { $$ = new Declaration($1, $2); }
	;

declaration_specifiers
	: storage_class_specifier
	| storage_class_specifier declaration_specifiers { $$ = new Typedef(*$1, $2); delete $1; }
	| type_specifier { $$ = $1; }
	| type_specifier declaration_specifiers { $$ = new Typedef($1->GetStr() , $2); }
	;

init_declarator_list
	: init_declarator { $$ = new InitDeclarationList($1); }
	| init_declarator_list ',' init_declarator { $1->PushBack($3); $$=$1; }
	;

init_declarator
	: declarator { $$ = new InitDeclaration($1, nullptr); }
	| declarator '=' initializer { $$ = new InitDeclaration($1, $3); }
	;

storage_class_specifier
	: TYPEDEF { $$ = new std::string("typedef"); }
	| EXTERN
	| STATIC
	| AUTO
	| REGISTER
	;

type_specifier
	: VOID { $$ = new TypeSpecifier("void"); }
	| CHAR { $$ = new TypeSpecifier("char"); }
	| SHORT
	| INT { $$ = new TypeSpecifier("int");}
	| LONG
	| FLOAT	 { $$ = new TypeSpecifier("float"); }
	| DOUBLE {$$ = new TypeSpecifier("double"); }
	| SIGNED { $$ = new TypeSpecifier("signed"); }
	| UNSIGNED { $$ = new TypeSpecifier("unsigned"); }
    | struct_specifier
	| enum_specifier
	| TYPE_NAME { $$ = new TypeSpecifier(*$1); delete $1; }
	;

struct_specifier
	: STRUCT IDENTIFIER '{' struct_declaration_list '}'
	| STRUCT '{' struct_declaration_list '}'
	| STRUCT IDENTIFIER
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator
	: declarator
	| ':' constant_expression
	| declarator ':' constant_expression
	;

enum_specifier
	: ENUM '{' enumerator_list '}'
	| ENUM IDENTIFIER '{' enumerator_list '}'
	| ENUM IDENTIFIER
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator
	: IDENTIFIER
	| IDENTIFIER '=' constant_expression
	;

declarator
	: pointer direct_declarator { $$ = new Pointer($2->GetStr(), nullptr); }
	| direct_declarator { $$ = $1; }
	;


direct_declarator
	: IDENTIFIER {
		 $$ = new Identifier(*$1, false, nullptr);
		delete $1;
	}
	| '(' declarator ')'
	| direct_declarator '[' constant_expression ']'  { $$ = new Array($1->GetStr(), $3->GetValue(), nullptr); }
	| direct_declarator '[' ']'
	| direct_declarator '(' parameter_list ')' { $1->ChangeIsFunction(true, $3); }

	| direct_declarator '(' identifier_list ')'  { $1->ChangeIsFunction(true, $3); }
	| direct_declarator '(' ')' { $1->ChangeIsFunction(true, nullptr); }
	;

pointer
	: '*'	{ $$ = new std::string("*"); }
	| '*' pointer { $$ = new std::string("*" + *$2);
	delete $2; }
	;

parameter_list
	: parameter_declaration { $$ = new NodeList($1); }
	| parameter_list ',' parameter_declaration { $1->PushBack($3); $$=$1; }
	;

parameter_declaration
	: declaration_specifiers declarator {
		$$ = new ParameterDeclaration($1, $2);
	}
	| declaration_specifiers abstract_declarator
	| declaration_specifiers
	;

identifier_list
	: IDENTIFIER	{ $$ = new NodeList(new Identifier(*$1, false, nullptr)); delete $1; }
	| identifier_list ',' IDENTIFIER { $1->PushBack(new Identifier(*$3, false, nullptr)); delete $3; $$=$1; }
	;

type_name
	: specifier_qualifier_list
	| specifier_qualifier_list abstract_declarator
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' constant_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' constant_expression ']'
	| '(' ')'
	| '(' parameter_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_list ')'
	;

initializer
	: assignment_expression
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	;

initializer_list
	: initializer { $$ = new NodeList($1); }
	| initializer_list ',' initializer { $1->PushBack($3); $$=$1; }
	;

statement
	: labeled_statement
	| compound_statement	{ $$ = $1; }
	| expression_statement  { $$ = $1; }
	| selection_statement
	| iteration_statement
	| jump_statement { $$ = $1; }
	;

labeled_statement
	: IDENTIFIER ':' statement
	| CASE constant_expression ':' statement { $$ = new ControlCase($2, $4);}
	| DEFAULT ':' statement { $$ = new ControlCase(nullptr,$3); }
	;

compound_statement
	: '{' '}' {
		$$ = new CompoundStatement(nullptr, nullptr);
        }
	| '{' statement_list '}' {
		$$ = new CompoundStatement(nullptr, $2);
	}
	| '{' declaration_list '}' {
		$$ = new CompoundStatement($2, nullptr);
	}
	| '{' declaration_list statement_list '}'  {
		$$ = new CompoundStatement($2, $3);
	}
	;

declaration_list
	: declaration { $$ = new NodeList($1); }
	| declaration_list declaration { $1->PushBack($2); $$=$1; }
	;

statement_list
	: statement { $$ = new NodeList($1); }
	| statement_list statement { $1->PushBack($2); $$=$1; }
	;

expression_statement
	: ';'
	| expression ';' { $$ = $1; }
	;

selection_statement
	: IF '(' expression ')' statement {$$ = new ControlIfElse{ $3, $5, nullptr};}
	| IF '(' expression ')' statement ELSE statement {$$ = new ControlIfElse{ $3, $5, $7};}
	| SWITCH '(' expression ')' statement { $$ = new ControlSwitch($3, $5); }
	;

iteration_statement
	: WHILE '(' expression ')' statement { $$ = new ControlWhile($3, $5, false); }
	| DO statement WHILE '(' expression ')' ';' { $$ = new ControlWhile($5, $2, true); }
	| FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement { $$ = new ControlFor($3, $4, $5, $7); }
	;

jump_statement
	: GOTO IDENTIFIER ';'
	| CONTINUE ';'
	| BREAK ';' { $$ = new ControlBreak(); }
	| RETURN ';' {
		$$ = new ReturnStatement(nullptr);
	}
	| RETURN expression ';' {
		$$ = new ReturnStatement($2);
	}
	;
%%

Node *g_root;

Node *ParseAST(std::string file_name)
{
  yyin = fopen(file_name.c_str(), "r");
  if(yyin == NULL){
    std::cerr << "Couldn't open input file: " << file_name << std::endl;
    exit(1);
  }
  g_root = nullptr;
  yyparse();
  return g_root;
}
