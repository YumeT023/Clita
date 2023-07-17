#ifndef CLITA_PARSER_H
#define CLITA_PARSER_H

#include "lexer.h"

typedef enum {
    Program,
    SymbolDeclaration,
    SymbolAssignment,
    SymbolLiteral,
    NumericLiteral,
    BinaryExpr,    // kajy
    ComparisonExpr,// vina
    UnaryExpr,
    Pragma
} NodeType;

typedef struct {
    NodeType type;
    char *name;
} SymbolLiteralNode;

typedef struct {
    NodeType type;
    int value;
} NumericLiteralNode;

typedef struct {
    NodeType type;
    NumericLiteralNode *left;
    char *op;// + , - , * , /
    NumericLiteralNode *right;
} BinaryExprNode;

typedef struct {
    NodeType type;
    NumericLiteralNode *left;
    char *op;// <, <=, >, >=, =
    NumericLiteralNode *right;
} ComparisonExprNode;

typedef struct {
    NodeType type;
    char op;// '-'
    NumericLiteralNode *expr;
} UnaryExprNode;

typedef struct {
    NodeType type;
    SymbolLiteralNode *identifier;
    NumericLiteralNode *initialValue;
} SymbolDeclarationNode;

typedef struct {
    NodeType type;
    SymbolLiteralNode *identifier;
    NumericLiteralNode *value;
} SymbolAssignmentNode;

typedef struct {
    NodeType type;
    char *name;
    NumericLiteralNode *argument;
} PragmaNode;

typedef struct {
    NodeType type;
} ProgramNode;

typedef struct {
    Token *tokens;
    size_t tokens_len;
    size_t pos;
} Parser;

Parser create_parser(Lexer *l);

Token *consume(Parser *p);
Token *p_peek(Parser *p);

SymbolDeclarationNode *parse_symbol_declaration(Parser *p);
SymbolAssignmentNode *parse_symbol_assignment(Parser *p);
SymbolLiteralNode *parse_symbol_literal(Parser *p);
NumericLiteralNode *parse_numeric_literal(Parser *p);
BinaryExprNode *parse_binary_expr(Parser *p);
ComparisonExprNode *parse_comparison_expr(Parser *p);
UnaryExprNode *parse_unary_expr(Parser *p);
PragmaNode *parse_pragma(Parser *p);
ProgramNode parse(char *source_text);

#endif//CLITA_PARSER_H
